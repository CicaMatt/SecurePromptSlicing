import sys

def get_value_at_index():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            return sys.argv[index]
        except (IndexError, ValueError):
            print("Invalid input or index out of range.")
            return None
    else:
        print("No additional arguments provided.")
        return None

if __name__ == "__main__":
    value = get_value_at_index()
    if value is not None:
        print(value)