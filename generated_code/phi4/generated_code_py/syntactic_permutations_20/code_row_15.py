import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <value>")
        return
    
    try:
        input_value = float(sys.argv[1])
        offset = 10.0  # Replace with your desired constant offset value
        result = input_value + offset
        print(f"Result after adding offset: {result}")
    except ValueError:
        print("Please provide a valid numeric value.")

if __name__ == "__main__":
    main()