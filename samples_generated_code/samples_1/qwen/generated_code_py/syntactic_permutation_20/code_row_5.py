import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <value>")
        return
    
    try:
        value = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        return
    
    offset = 5.0  # Define the constant offset here
    result = value + offset
    print(f"Result: {result}")

if __name__ == "__main__":
    main()