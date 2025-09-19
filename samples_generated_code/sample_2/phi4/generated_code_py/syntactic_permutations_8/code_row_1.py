import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Error: Not enough arguments")
        return
    
    try:
        index = int(sys.argv[1])
        values = sys.argv[2:]
        if index < 0 or index >= len(values):
            print(f"Index {index} out of range")
        else:
            print(values[index])
    except ValueError:
        print("Error: The first argument must be an integer")

if __name__ == "__main__":
    get_value_at_index()