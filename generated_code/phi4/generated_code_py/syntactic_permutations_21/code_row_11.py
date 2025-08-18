import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <value>")
        return 1
    
    value = sys.argv[1]
    print(value)
    return 0

if __name__ == "__main__":
    sys.exit(main())