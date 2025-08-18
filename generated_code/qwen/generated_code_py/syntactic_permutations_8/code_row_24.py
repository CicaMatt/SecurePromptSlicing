import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <string1> [string2 ... stringN]")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        return
    
    args = sys.argv[2:]
    
    if index < 0 or index >= len(args):
        print("Index out of range.")
        return
    
    print(args[index])

if __name__ == "__main__":
    main()