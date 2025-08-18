import sys

def get_value_from_argv():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            return sys.argv[index]
        except (ValueError, IndexError):
            print("Invalid index or insufficient arguments.")
    else:
        print("Insufficient arguments.")

if __name__ == "__main__":
    result = get_value_from_argv()
    if result is not None:
        print(result)