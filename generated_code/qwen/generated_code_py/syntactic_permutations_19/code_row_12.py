import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        number = float(sys.argv[1])
        result = number + 5
        print(f"The result is: {result}")
    except ValueError:
        print("Please provide a valid number.")

if __name__ == "__main__":
    main()