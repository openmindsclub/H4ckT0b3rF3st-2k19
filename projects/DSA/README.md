## Digital Signature Algorithm
this is a Python Implementation of the DSA,it's a mechanism of signing arbitrary messages and verifying signatures safely.

### Setup
You need to install some libs:
```bash
pip install pycrypto
pip install sympy
```

### Usage
This implementation features Three main things:
* Key generation
* Signing
* Verifying

to generate Primes,call the generatePrimes method which takes the length of P in bits and returns P and Q:
```python
>>> p,q = DSA.generatePrimes(3072)
>>> p,q = hex(p),hex(q)
>>> print p,q
0xf10fd6c6a9d65ca00de3bcb55b375b491dcf59bab048b4fe75651b6987b64b8206f063b86108426e408003c6d6cd49a06c521132bd88b97312be21cf17508efcaec8861100028cc515050708b1b0421348e7e931275819ce0e12340b1af838060053979c9de0ca52117760818b4ef366ebab5192550c2cf405f3c169bd407de1 0xaa3a9d7dcfbd0f06b31b1f253ee364334b50e079
```
the G,X,Y paramaters are generated automatically when you instanciate a new instance,although you can pass your own paramaters to the new instance

to sign a message:
```python
>>> dsa = DSA()
>>> msg = "Sign The World!"
>>> r,s = dsa.sign(msg)
>>> print r,s
5681864235740193460024999109060421585894964780585390665554542705382681221272 1376955150519237565016762723285531351092721079098346701441871564153575832933
```

to verify a signature:
```python
>>> dsa.verify(r,s,msg)
True
```

### Tasks
Here are things you can do to complete this implementation:
* Write the signing method
* Write the verifying method
* Write the `__str__` method
* Add checks to the `sign` and `verify` methods
* Add support for other Hashing Algorithms

### Ressources
* [Digital Signature Algorithm](https://en.wikipedia.org/wiki/Digital_Signature_Algorithm)

#### Happy Hacking!
