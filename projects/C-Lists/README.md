# C-Lists

This is an implementation of Linked Lists in C
it is meant to be as easy to use as Python lists.
You can put in it any type of value (int, float, char, string)

## Usage

You can use it like this:

```c
List* l = list_init();
list_add_int(l,1337);
list_add_float(l,19.69);
list_add_char(l,'R');
list_print(l);
```

Output:

```c
['R' , 5.900000 , 1337 , 0]
```

To compile it:

```bash
gcc main.c list.c -o mylist
```

## Tasks

1. You may have noticed that a value 0 is automatically added when you initialize the list. FIX IT !!

2. Currently only 3 types of data are supported: int, float, and char. We want to use strings as well. ADD IT !!

3. Any value you add will be added at the begining, keep it but add other functions to append at the end of the list.

4. Add some useful functions like: 
   - list_size(List* l)
   - list_remove(int index)
   - list_destroy(List* l)
   - list_getvalue(int index)
   - list_getindex(int value)

5. Be creative :)

### Enjoy
