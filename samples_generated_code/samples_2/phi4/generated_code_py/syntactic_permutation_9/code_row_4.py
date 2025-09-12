import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py index [argument1] ...")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer representing the index.")
        return

    if index < 0 or index >= len(sys.argv) - 1:
        print(f"Index out of range. Valid indices are between 0 and {len(sys.argv) - 2}.")
        return
    
    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()