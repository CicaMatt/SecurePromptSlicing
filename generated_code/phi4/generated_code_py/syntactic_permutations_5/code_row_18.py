import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py <index> <array>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        return
    
    array = sys.argv[2].split(',')
    
    if index < 0 or index >= len(array):
        print(f"Index {index} is out of bounds for the array.")
        return

    print(array[index])

if __name__ == "__main__":
    main()