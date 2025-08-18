import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one integer as an argument.")
        return
    
    try:
        value = int(sys.argv[1])
    except ValueError:
        print("The provided argument is not a valid integer.")
        return
    
    result = value + 1
    print(result)
    return

if __name__ == "__main__":
    main()