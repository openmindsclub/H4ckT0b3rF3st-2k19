# Python Beginner Soup: Lists

Welcome to Python Beginner Soup! This is a soup of short python snippets. But for an unknown reason, most of these codes are returning some kind of *error*... I'm a total sucker at Python, can you please help me find the errors and correct them?

## How To Contribute

In each snippet, you can contribute either by correcting **spelling mistakes**, **syntax** or **semantics errors**, or, if you're feeling crazy, you can contribute by **improving the code** altogether!

Sometimes, the code can be shortened to *one line* of Python... Don't worry, the changes that need to be done will all be specified in each snippet!

## Documentation

You may need to use:

## String Things
In Python, you can do a lot of interesting things with strings:

**Splitting strings:**
```
>>> tmpstring = "hadi string ya kho"
>>> result = tmpstring.split("a")
```
At the end, `result` will contain the list:
```
['h', 'di string y', 'kho']
```
The snippet below removes all white spaces:
```
>>> tmpstring = "  hadi      string    ya   kho "
>>> result = tmpstring.split()

```
Then the `result` contains:
```
['hadi', 'string', 'ya', 'kho']
```

**Joining strings:**
</br>You can also `join` things together:
```
>>> listofstrings = ['h', 'a', 'c', 'k']
>>> result = "//".join(listofstrings)
```
The the result will contains:
```
h//a//c//k
```
Just like with `split`, in `join` if you don't add any character, it merges the elements of the list together:

```
>>> listofstrings = ['OP3N', 'M1ND5', 'CLUB']
>>> result = "".joing(listofstrings)

```

Then the `result` contains:
```
Op3NM1ND5CLUB
```
See the [Python documentation about strings](https://docs.python.org/3.3/library/stdtypes.html?highlight=set#set) for more information.

### List comprehension

The idea behind list comprehension is to condense the for loop and the list appending into one simple line. You can also embed if statements into the list comprehension — check out [this reference](https://docs.python.org/3/library/string.html) to help you out.

**Example:**
We want to create a list of squares:
```
>>> squares = []
>>> for x in range(10):
...     squares.append(x**2)
...
>>> squares
[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
```
We can equivalently write it like this:
```
squares = [x**2 for x in range(10)]
```
Which is more readable.

### Sets:
The features of sets are:
* They are not ordered
* There are no repeated elements in sets
* You can convert between sets and lists very easily
In Python, you can make a set with the `set()` keyword.

**Example:**
```
>>> names = set()
>>> names.add("Khedouj")
>>> names.add("Illidan")
>>> names.add("Khedouj")
>>> print(names)
```
And the output will be:
```
set(['Khedouj', 'Illidan'])
```
You can also convert from a list to a set and from a set to a list:
```
>>> names = ["Khedouj", "Illidan", "Catch-22", "Khedouj"]
>>> names = set(names)
>>> names = list(names)
>>> print(names)
```
And the output will be:
```
['Khedouj', 'Illidan', 'Catch-22']
```
See the [Python documentation about sets](https://docs.python.org/3.3/library/stdtypes.html?highlight=set#set) for more information.
