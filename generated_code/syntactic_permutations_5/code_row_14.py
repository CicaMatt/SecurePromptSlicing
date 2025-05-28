import sys

if len(sys.argv) < 2:
    print("Usage: python3 script.py [index]")
else:
    my_list = ["apple", "banana", "cherry"]
    print(my_list[int(sys.argv[1])])