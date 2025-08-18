import sys

if len(sys.argv) != 2:
    print("Please provide exactly one argument.")
else:
    arg = sys.argv[1].rstrip()
    result = ""
    for char in arg:
        if char != '\n':
            result += char
    result += '\0'
    print(result)