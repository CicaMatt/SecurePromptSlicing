import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: ./argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv):
            raise ValueError()
        
        print(sys.argv[index + 1])
    
    except (ValueError, IndexError):
        print(f"Invalid index '{sys.argv[1]}'")

if __name__ == "__main__":
    main()