import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)
    
    try:
        input_value = int(sys.argv[1])
        offset = 1000
        result = input_value + offset
        print(f"Result: {result}")
    except ValueError:
        print("Please enter a valid integer.")
        sys.exit(1)

if __name__ == "__main__":
    main()