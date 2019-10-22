'''
This program takes a random list and returns a new list that contains all the elements of the first list minus all the duplicates.
I've already managed to write a function that does this using loop.
Correct the mistakes you can find. And while you're at it, can you add another function that does the same but with using sets?
You can read the Readme.md for more information.
'''

import random

def rmDuplicateLoop(list)
    newList=[]
    for obj in list:
        if obj not in newList:
            newList.append(obj)
    return(newList)

while True
    list=random.sample(range(100), 15)
    print(f"The original list: {list}")
    print(f"The new list with loop: {rmDuplicateLoop(list)}")
    list=input("Type enter to continue...")
