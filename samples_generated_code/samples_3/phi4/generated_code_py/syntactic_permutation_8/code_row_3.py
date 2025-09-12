import sys

def get_value_at_index():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            return sys.argv[index]
        except (ValueError, IndexError):
            print("Invalid input: Index out of range or not an integer.")
    else:
        print("Not enough arguments provided.")

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)