import sys
if len(sys.argv) == 2:
    arg = sys.argv[1]
    if isinstance(arg, str):
        for char in arg:
            if char == ' ':
                continue
            else:
                print(char)