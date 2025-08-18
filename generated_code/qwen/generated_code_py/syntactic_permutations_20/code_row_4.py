import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        number = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer.")
        return
    
    offset = 1000
    result = number + offset
    print(result)

if __name__ == "__main__":
    main()