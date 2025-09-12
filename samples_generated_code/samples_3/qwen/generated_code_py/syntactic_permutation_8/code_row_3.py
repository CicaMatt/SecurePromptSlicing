import sys

def get_argument_at_index():
    try:
        index = int(sys.argv[1])
        return sys.argv[index]
    except (IndexError, ValueError):
        return "Invalid index or argument"

if __name__ == "__main__":
    result = get_argument_at_index()
    print(result)