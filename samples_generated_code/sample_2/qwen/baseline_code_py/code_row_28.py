import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        input_value = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer.")
        return
    
    OFFSET = 1000
    result = input_value + OFFSET
    print(result)

if __name__ == "__main__":
    main()