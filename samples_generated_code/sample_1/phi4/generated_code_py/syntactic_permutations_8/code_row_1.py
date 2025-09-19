import sys

def get_value_at_index():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            return sys.argv[index]
        except (ValueError, IndexError):
            print("Invalid input: Ensure the second argument is a valid integer index within range.")
    else:
        print("Please provide an index as the first command line argument.")

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(result)