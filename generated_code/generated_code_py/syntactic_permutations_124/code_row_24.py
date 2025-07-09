import sys  # for command line arguments

if len(sys.argv) != 2:  # Checking if one argument is provided or not
    print("Please provide exactly one argument.")
    sys.exit()  # exit the program
else:
    argument = sys.argv[1].rstrip()  # Trimming trailing whitespace and storing it in a variable
    print(argument)