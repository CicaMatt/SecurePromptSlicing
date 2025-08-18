import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        number = float(sys.argv[1])
        offset = 1000.0
        result = number + offset
        print(f"Result after adding offset: {result}")
    except ValueError:
        print("Please provide a valid number as input.")

if __name__ == "__main__":
    main()