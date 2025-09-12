import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide an index as an argument.")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv):
            print(f"Index {index} is out of range. Please enter a valid index between 0 and {len(sys.argv) - 1}.")
            return
        print(sys.argv[index + 1])
    except ValueError:
        print("Please provide a valid integer as the first argument.")

if __name__ == "__main__":
    main()