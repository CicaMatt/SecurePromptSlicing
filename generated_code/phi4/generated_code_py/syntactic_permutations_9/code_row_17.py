import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide an index.")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv):
            print(f"Index {index} is out of range. Valid indices are from 0 to {len(sys.argv) - 1}.")
            return
        
        print(sys.argv[index + 1])
    except ValueError:
        print("The provided index must be an integer.")

if __name__ == "__main__":
    main()