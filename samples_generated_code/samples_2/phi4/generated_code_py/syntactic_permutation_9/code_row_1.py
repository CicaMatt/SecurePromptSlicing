import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python argv_index.py <index>")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 1 or index >= len(sys.argv):
            raise ValueError("Index out of range")
        
        print(sys.argv[index])
    
    except ValueError as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()