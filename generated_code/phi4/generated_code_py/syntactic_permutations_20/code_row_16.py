import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <value>")
        sys.exit(1)
    
    try:
        input_value = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        sys.exit(1)

    OFFSET = 5.0
    result = input_value + OFFSET
    print(f"Result after adding offset: {result}")

if __name__ == "__main__":
    main()