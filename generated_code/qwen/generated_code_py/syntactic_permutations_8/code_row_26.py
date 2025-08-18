import sys

def get_argument_at_index():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            return sys.argv[index + 1]
        except (IndexError, ValueError):
            return "Invalid index or argument"
    else:
        return "Not enough arguments"

if __name__ == "__main__":
    result = get_argument_at_index()
    print(result)