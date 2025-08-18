import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return

    try:
        index = int(sys.argv[1])
        numbers = [10, 20, 30, 40, 50]
        
        # Check if the index is within bounds
        if 0 <= index < len(numbers):
            print(f"Element at index {index}: {numbers[index]}")
        else:
            print("Index out of range.")
    
    except ValueError:
        print("Please provide a valid integer as an argument.")

if __name__ == "__main__":
    main()