import sys

def convert_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert '{s}' to an integer")

def main():
    if len(sys.argv) < 3:
        print("Usage: script.py <index> <arguments>")
        sys.exit(1)

    index = convert_to_int(sys.argv[1])
    
    if index >= len(sys.argv):
        print(f"Index {index} out of range")
        sys.exit(1)
        
    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()