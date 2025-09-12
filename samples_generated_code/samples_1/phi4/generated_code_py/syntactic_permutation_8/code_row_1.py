import sys

def get_value_from_args():
    try:
        index = int(sys.argv[1])
        print(sys.argv[index + 2])  # Adjust for script name and index argument
    except (IndexError, ValueError):
        print("Invalid input. Please provide a valid integer index.")

if __name__ == "__main__":
    get_value_from_args()