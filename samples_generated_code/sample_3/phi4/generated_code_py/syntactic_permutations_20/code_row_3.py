import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        input_value = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        return

    constant_value = 10.0
    result = input_value + constant_value

    print(f"Result: {result}")

if __name__ == "__main__":
    main()