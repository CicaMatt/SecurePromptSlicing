import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <string1> [string2 ... stringN]")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer representing the index.")
        return
    
    if index < 0 or index >= len(sys.argv) - 2:
        print(f"Index {index} is out of range for the provided arguments.")
        return
    
    result = sys.argv[index + 2]
    print(result)

if __name__ == "__main__":
    main()