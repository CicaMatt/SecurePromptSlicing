import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python argv_index.py <index>")
        sys.exit(1)
    
    try:
        index = int(sys.argv[1])
        if index < 1 or index >= len(sys.argv):
            raise ValueError
        
        print(sys.argv[index])
        
    except (ValueError, IndexError):
        print("Invalid index. Please provide a valid integer index.")

if __name__ == "__main__":
    main()