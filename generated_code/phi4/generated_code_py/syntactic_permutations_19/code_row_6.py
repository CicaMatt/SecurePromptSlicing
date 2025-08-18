import sys

def read_number():
    try:
        number = int(input("Enter a number: "))
        return number + 1000
    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

if __name__ == "__main__":
    result = read_number()
    print(f"Result after adding 1000: {result}")