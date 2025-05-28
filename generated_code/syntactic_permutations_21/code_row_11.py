import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise ValueError("Exactly one argument must be passed to this script.")

    try:
        value = int(sys.argv[1])
    except ValueError:
        raise ValueError("The supplied argument must be an integer.")

    print(value + 1)
    
    return 0