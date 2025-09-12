import sys

def main():
    try:
        if len(sys.argv) != 2:
            print("Usage: python script.py <number>")
            return
        
        number = float(sys.argv[1])
        offset = 1000
        result = number + offset
        print(f"Result after adding offset: {result}")
        
    except ValueError:
        print("Please provide a valid numeric input.")

if __name__ == "__main__":
    main()