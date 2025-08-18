import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    sys.exit()

the_argument = sys.argv[1]
the_argument = the_argument.rstrip()
print(the_argument)
sys.exit()