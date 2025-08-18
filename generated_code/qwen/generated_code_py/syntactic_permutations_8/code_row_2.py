import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <list of strings>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer.")
        return

    args = sys.argv[2:]
    
    if index < 0 or index >= len(args):
        print("Index out of range.")
        return

    print(args[index])

if __name__ == "__main__":
    get_value_at_index()