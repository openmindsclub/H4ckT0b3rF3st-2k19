#!/usr/bin/env python2
from  string import lowercase, uppercase
from itertools import cycle
import sys

def documentation():
	f = open('documentation.txt', 'r')
	doc = f.read()
	print doc
	f.close()


def vigenereEncrypt(plain_text, key):
	cipher_text = ''
	keyStep=cycle([lowercase.find(k) if lowercase.find(k) !=-1 else 0 for k in key.lower()])
	for letter in plain_text:
		if letter in lowercase:
			cipher_text += lowercase[( lowercase.find(letter ) + next(keyStep)) % 26]
		elif letter in uppercase:
			cipher_text += uppercase[( uppercase.find(letter ) + next(keyStep)) % 26]
		else :
			cipher_text += letter
	return cipher_text


if __name__ == '__main__':
	if len(sys.argv) == 2:
		if sys.argv[1] == '--interactive' :
			text = str( raw_input('Enter plain text : ') )
			keyword  = str( raw_input('Enter encryption key : ') )
			cipher = vigenereEncrypt(text, keyword)
			print 'Encrypted text : '
			print cipher
	else :
		documentation()
