import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        input_value = float(sys.argv[1])
        offset = 1000.0
        result = input_value + offset
        print(f"Result after adding offset: {result}")
    except ValueError:
        print("Please provide a valid number as an argument.")

if __name__ == "__main__":
    main()