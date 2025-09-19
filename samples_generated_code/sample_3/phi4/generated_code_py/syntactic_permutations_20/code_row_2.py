import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        input_value = float(sys.argv[1])
    except ValueError:
        print("Please enter a valid number.")
        return
    
    offset = 1000
    result = input_value + offset
    print(f"Result after adding offset of {offset}: {result}")

if __name__ == "__main__":
    main()