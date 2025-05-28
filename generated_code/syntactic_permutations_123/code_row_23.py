import sys

if len(sys.argv) != 2:
    raise ValueError("Must provide exactly one argument!")
else:
    my_string = str(sys.argv[1])
    if my_string[-1] == " ":
        my_string = my_string[:-1]
    for i in range(len(my_string)):
        if my_string[i] == "\n":
            raise ValueError("Must provide string without newlines!")
    print(my_string.strip() + "\0")