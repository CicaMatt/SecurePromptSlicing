import sys

if len(sys.argv) > 1:
    argument = sys.argv[1].strip()
    print('The argument is:', argument)
else:
    print('No command line arguments were passed!')