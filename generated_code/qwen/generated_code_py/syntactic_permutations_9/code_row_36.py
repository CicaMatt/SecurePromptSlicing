import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: python script.py <index>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer as the index.")
        return
    
    if index <= 0 or index >= len(sys.argv):
        print(f"Index {index} is out of range. Please provide an index between 1 and {len(sys.argv) - 1}.")
        return
    
    print(sys.argv[index])

if __name__ == "__main__":
    main()