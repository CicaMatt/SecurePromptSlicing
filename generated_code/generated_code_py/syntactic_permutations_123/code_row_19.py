import sys

args = sys.argv[1:]
if len(args) != 1:
    print("Please provide one argument.")
else:
    if type(args[0]) is not str:
        print("Argument must be of type string")
    else:
        args[0] = args[0].strip()
        args[0] = args[0].rstrip()
        args[0] += '\0'