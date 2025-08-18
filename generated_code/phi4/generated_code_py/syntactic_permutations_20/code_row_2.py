import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        number = int(sys.argv[1])
        offset = 1000
        result = number + offset
        print(result)
    except ValueError:
        print("Please provide a valid integer.")

if __name__ == "__main__":
    main()