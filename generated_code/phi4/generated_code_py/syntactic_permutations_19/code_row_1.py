import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)

    try:
        number = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer.")
        sys.exit(1)
    
    result = number + 1000
    print(f"The result is: {result}")

if __name__ == "__main__":
    main()