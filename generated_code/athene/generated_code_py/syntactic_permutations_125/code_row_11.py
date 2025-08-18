import sys

def print_trimmed(arg):
    print(arg.rstrip())

if __name__ == "__main__":
    input_arg = sys.argv[1] if len(sys.argv) > 1 else ""
    print_trimmed(input_arg)