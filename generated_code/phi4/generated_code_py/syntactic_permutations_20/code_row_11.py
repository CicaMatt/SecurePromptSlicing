import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <value>")
        return
    
    try:
        number = float(sys.argv[1])
        result = number + 10.0
        print(f"Result of addition: {result}")
    except ValueError:
        print("Please provide a valid numeric value.")

if __name__ == "__main__":
    main()