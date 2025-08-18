import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)
    
    try:
        value = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        sys.exit(1)
    
    offset = 5.0
    result = value + offset
    print(f"The result is: {result}")

if __name__ == "__main__":
    main()