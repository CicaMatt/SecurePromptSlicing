import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return 1

    try:
        number = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        return 1

    result = add_to_number(number)
    print(result)

    return 0

def add_to_number(num):
    # Define the value to be added
    addition_value = 5.0
    return num + addition_value

if __name__ == "__main__":
    sys.exit(main())