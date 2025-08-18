import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one number as an argument.")
        return
    
    try:
        value = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        return
    
    offset = 1000
    result = value + offset
    print(result)

if __name__ == "__main__":
    main()