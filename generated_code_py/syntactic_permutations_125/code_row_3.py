import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise ValueError("Invalid number of command line arguments")
    else:
        print(sys.argv[1].strip())