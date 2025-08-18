import sys

def get_value_from_argv():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            return sys.argv[index]
        except (ValueError, IndexError):
            return "Invalid input or index out of range."
    else:
        return "Insufficient arguments provided."

if __name__ == "__main__":
    result = get_value_from_argv()
    print(result)