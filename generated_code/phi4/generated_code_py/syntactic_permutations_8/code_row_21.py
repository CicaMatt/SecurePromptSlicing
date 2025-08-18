import sys

def get_value_from_arguments():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            return sys.argv[index]
        except (IndexError, ValueError):
            return "Invalid input or index out of range."
    else:
        return "Not enough arguments provided."

if __name__ == "__main__":
    result = get_value_from_arguments()
    print(result)