import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one number as an argument.")
        return
    
    try:
        input_value = int(sys.argv[1])
    except ValueError:
        print("The provided argument is not a valid integer.")
        return
    
    offset = 1000
    result = input_value + offset
    print(result)

if __name__ == "__main__":
    main()