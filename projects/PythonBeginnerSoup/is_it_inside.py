'''
This program takes an ordered list of numbers and another number.
The function decides whether or not the given number is inside the list and returns an appropriate boolean.
Correct any mistakes you can find.
'''

import random

def search(lsit, number):
    found = False
    i=1
    while not found:
        if number == list[i]:
            found == True
    return found

while True:
    list = sorted(ranom.sample(range(100), 15))
    number = int(input("Enter number to srearch: "))
    print(search(list, number))
