import sys

def get_value_from_args():
    if len(sys.argv) < 2:
        print("No index provided.")
        return
    
    try:
        index = int(sys.argv[1])
        if len(sys.argv) <= index + 1:
            print(f"No value found at index {index}.")
            return
        
        print(sys.argv[index + 1])
    except ValueError:
        print(f"Invalid index: {sys.argv[1]}. Index must be an integer.")

if __name__ == "__main__":
    get_value_from_args()