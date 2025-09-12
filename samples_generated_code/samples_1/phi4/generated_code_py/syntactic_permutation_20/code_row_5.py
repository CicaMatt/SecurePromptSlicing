import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <value>")
        sys.exit(1)

    try:
        input_value = float(sys.argv[1])
    except ValueError:
        print("Please enter a valid number.")
        sys.exit(1)
    
    OFFSET = 10.0
    result = input_value + OFFSET

    print(f"The value with offset added: {result}")

if __name__ == "__main__":
    main()