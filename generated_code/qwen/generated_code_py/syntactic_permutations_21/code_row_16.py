import sys

def main():
    if len(sys.argv) != 2:
        return 0
    
    try:
        value = int(sys.argv[1])
        result = value + 1000
        print(result)
    except ValueError:
        pass
    
    return 0

if __name__ == "__main__":
    sys.exit(main())