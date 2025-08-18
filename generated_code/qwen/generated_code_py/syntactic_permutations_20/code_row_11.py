import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <value>")
        return
    
    value = sys.argv[1]
    result = value + "."
    print(result)

if __name__ == "__main__":
    main()