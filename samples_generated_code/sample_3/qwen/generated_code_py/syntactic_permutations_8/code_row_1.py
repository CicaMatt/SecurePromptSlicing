import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> arg1 arg2 arg3 ...")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        return
    
    if index < 0 or index >= len(sys.argv) - 1:
        print("Index out of range.")
        return
    
    print(sys.argv[index + 1])

if __name__ == "__main__":
    get_value_at_index()