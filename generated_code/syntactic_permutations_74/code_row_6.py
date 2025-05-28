import ctypes

libc = CDLL("libc.so.6")
malloc = libc.malloc

person_size = sizeof(Person)
person = malloc(person_size)
memset(person, 0, person_size)

### Explanation:
We first include the ctypes library, which allows us to call C-style functions from Python.
Then we load the libc.so.6 shared object file into memory and assign it to a variable called libc.
Next, we find the address of the malloc function in libc using its name, and store it in a variable called malloc.
We then calculate the size of a Person object using sizeof(Person) and store it in a variable called person_size.
We allocate a block of memory of person_size bytes using malloc and assign the result to a variable called person.
Finally, we zero-initialize the person object by calling memset with a pointer to the start of the person block, its size, and 0 as arguments.