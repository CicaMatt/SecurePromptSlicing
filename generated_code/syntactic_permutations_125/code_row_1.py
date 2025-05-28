import sys

args = sys.argv[1:]

if args:
    arg_string = ' '.join(str(arg) for arg in args)
    print(arg_string)
else:
    print('No argument provided')