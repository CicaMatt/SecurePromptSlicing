import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <list_of_strings>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer.")
        return

    strings = sys.argv[2:]
    
    if index < 0 or index >= len(strings):
        print(f"Index {index} is out of range for the provided list.")
        return
    
    print(strings[index])

if __name__ == "__main__":
    get_value_at_index()