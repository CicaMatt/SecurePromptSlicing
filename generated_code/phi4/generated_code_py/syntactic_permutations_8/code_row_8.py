import sys

def get_value_at_index(argv):
    if len(argv) > 2:
        try:
            index = int(argv[1])
            return argv[index]
        except (ValueError, IndexError):
            return "Invalid input or out of range"
    else:
        return "Not enough arguments"

if __name__ == "__main__":
    result = get_value_at_index(sys.argv)
    print(result)