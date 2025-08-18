import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <list of strings>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        return
    
    args_list = sys.argv[2:]
    
    if index >= len(args_list) or index < 0:
        print(f"Index {index} is out of range for the provided list.")
        return
    
    print(args_list[index])

if __name__ == "__main__":
    main()