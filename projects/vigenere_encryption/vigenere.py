#!/usr/bin/env python
import string 
import sys

alpha  = string.lowercase
def documentation():
	f = open('documentation.txt', 'r')
	doc = f.read()
	print doc
	f.close()

def vigenereEncrypt(plain_text, key):
	cipher_text = ''
	i = 0
	k = 0
	while i < len(plain_text):
		if plain_text[i] in alpha:
			cipher_text += alpha[( alpha.find(plain_text[i] ) + alpha.find( key[k % len(key)] ) +1 ) % len(alpha)]
			i += 1
			k += 1
		else:
			cipher_text += plain_text[i]
			i += 1
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
