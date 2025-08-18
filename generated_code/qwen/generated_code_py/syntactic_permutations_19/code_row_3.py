import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        number = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        return
    
    result = number + 1000
    print(result)

if __name__ == "__main__":
    main()