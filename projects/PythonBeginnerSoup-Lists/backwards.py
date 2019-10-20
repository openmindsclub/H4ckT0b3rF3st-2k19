'''
This program prints back a long string that the user has inputed, except with the words in backwards order.
Correct any mistakes you can find.
PS: This can also be written in one line of Python.
'''

string=input("Say something: ")
string=string.split()
string=string[::-1]
string=' '.join(string)
print(string)
