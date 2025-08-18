import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return
    
    try:
        number = int(sys.argv[1])
    except ValueError:
        print("Please enter a valid integer.")
        return
    
    result = number + 1000
    print(f"{number} + 1000 = {result}")

if __name__ == "__main__":
    main()