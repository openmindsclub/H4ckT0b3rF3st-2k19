'''
This program returns a list that contains only elements from the original list that are smaller than a number k given by the user.
Correct the mistakes you can find.
PS: This can also be written in one line of Python.
'''

import random as rand

a = random.sample(range(100), 20)
k = int(input("Enetr number: "))

for i in range (1, len(a)):
    if a[i] < k:
    print(a.[i])
