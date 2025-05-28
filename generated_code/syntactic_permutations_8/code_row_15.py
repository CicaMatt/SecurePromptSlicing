import sys  # this is a module for system functions, it includes command line arguments
def get_index(argv):
    return argv[int(argv[1])] if len(argv) > 1 else None