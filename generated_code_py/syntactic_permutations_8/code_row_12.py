import sys  # System-specific parameters and functions

def get_index(argv):
    if len(sys.argv) == 2:  # Checks that only one argument is provided
        try:
            return int(argv[1])
        except ValueError as e:
            print("Argument must be a number.")
            exit()
    else:
        print("Please provide a single command line argument.")
        exit()