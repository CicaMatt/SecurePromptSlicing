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
    
    constant_value = 5
    result = number + constant_value
    print(f"The result of adding {constant_value} to {number} is: {result}")

if __name__ == "__main__":
    main()