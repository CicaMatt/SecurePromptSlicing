import sys

def get_argument_at_index():
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
        return None
    try:
        index = int(sys.argv[1])
        return sys.argv[index + 2]
    except (IndexError, ValueError):
        print("Invalid index or argument.")
        return None

if __name__ == "__main__":
    result = get_argument_at_index()
    if result is not None:
        print(result)