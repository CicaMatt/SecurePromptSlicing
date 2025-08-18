import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one number as an argument.")
        return
    
    try:
        number = float(sys.argv[1])
    except ValueError:
        print("The provided argument is not a valid number.")
        return
    
    result = number + 1000
    print(result)

if __name__ == "__main__":
    main()