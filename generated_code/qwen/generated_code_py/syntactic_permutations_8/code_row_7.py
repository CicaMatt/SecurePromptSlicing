import sys

def get_argument_value(argv):
    try:
        index = int(argv[1])
        return argv[index]
    except (IndexError, ValueError):
        return None

if __name__ == "__main__":
    result = get_argument_value(sys.argv)
    print(result)