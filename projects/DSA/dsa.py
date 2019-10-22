from hashlib  import sha1
from os import urandom
from sympy import isprime
from Crypto.Util.number import inverse


class DSA:
	def __init__(self,p = None,q = None,g = None,public = None,private = None):
		if p == None or q == None:
			self.p = None
			self.q = None
			self.g = None
			self.generateKeys()
		else:
			self.p = p
			self.q = q

		if g == None: self.generateParamaters()
		else: self.g = g

		if public == None: self.generateKeys()
		else:
 			self.public = public
			self.private = private

	@staticmethod
	def generatePrimes(L = 1024):
		acceptableLengths = {1024:160,2048:256,3072:256}
		if L not in acceptableLengths:
			print "[-] Unacceptable Length"
			return 0,0
		nBytes = acceptableLengths[L] / 8 + 1
		while True:
			while True:
				while True:
					seed = urandom(nBytes)
					if(int(seed.encode("hex"),16)>(2 ** acceptableLengths[L])):
						break
		
				g = nBytes * 8
				s1 = int(sha1(seed).hexdigest(),16)
				s2 = int(seed.encode("hex"),16) + 1
				s2 %= (2 ** g)
				s2 = hex(s2)[2:].rstrip("L")
				if(len(s2) % 2 == 1):
					s2 = "0" + s2
				s2 = s2.decode("hex")
				s2 = int(sha1(s2).hexdigest(),16)
		
				u = s1 ^ s2
				q = u | 2 ** (acceptableLengths[L] - 1) | 1
				if(isprime(q)):
					break
			counter,offset = 0,2
			n = (L-1) // acceptableLengths[L]
			b = (L-1) % acceptableLengths[L]
			while counter < 4096:
				V = []
				for k in range(n + 1):
					tmp = int(seed.encode("hex"),16) + offset + k
					tmp %= (2 ** g)
					tmp = hex(tmp)[2:].rstrip("L")
					if(len(tmp) % 2 == 1):
						tmp = "0" + tmp
			
					tmp = int(sha1(tmp.decode("hex")).hexdigest(),16)
					V.append(tmp)
				W = 0
				for j,i in enumerate(V[:-1]):
					W += i * (2 ** (j * acceptableLengths[L]))
				W += (V[-1] % (2 ** b)) * (2 ** (n*acceptableLengths[L]))
				X = W + (2 ** (L-1))
				c = X % (2*q)
				p = X - (c - 1)
				if(p >= (2 ** (L-1)))and(isprime(p)):
					return p,q
				else:
					counter += 1
					offset += n + 1
		
	def generateParamaters(self):
		if self.q == None or self.p == None: self.p,self.q = self.generatePrimes(3072)
		while True:
			self.g = pow(2,(self.p - 1) / self.q, self.p)
			if self.g != 1: break

	def generateKeys(self):
		if self.g == None: self.generateParamaters()
		while True:
			self.private = int(urandom(20).encode("hex"),16)
			if self.private < self.q: break
		self.public = pow(self.g,self.private,self.p)
	
	def sign(self,msg):
		if self.private == None or self.public == None: self.generateKeys()
		while True:
			while True:
				while True:
					k = int(urandom(19).encode("hex"),16)
					if(k < self.q):
							break
				r = pow(self.g,k,self.p) % self.q
				if(r != 0):
					break
		
			h = int(sha1(msg).hexdigest(),16)
			s = (inverse(k,self.q) * (h + (self.private * r))) % self.q
			if(s != 0):
				break
		return r,s

	def verify(self,r,s,msg):
		try:
			assert ((r < self.q)and(r > 0))
			assert ((s < self.q)and(s > 0))
		except:
			print "[-] Invalid Signature"
			return
		
		w = inverse(s,self.q) % self.q
		h = int(sha1(msg).hexdigest(),16)
		u1 = (h * w) % self.q
		u2 = (r * w) % self.q
		v1 = pow(self.g,u1,self.p)
		v2 = pow(self.public,u2,self.p)
		v = ((v1 * v2)% self.p) % self.q
		if(v == r):
			print "[+] Signature confirmed"
			return True
		else:
			print "[+] Calculated Value: " + str(v)
			print "[+] Expected Value: " + str(r)
			print "[-] Invalid signature"
			return False

if(__name__=="__main__"):
	dsa = DSA()
	print dsa#should output all the paramaters,preferably in hex
	msg = "hello world"
	r,s = dsa.sign(msg)
	print r,s
	dsa.verify(r,s,msg)#must return True
