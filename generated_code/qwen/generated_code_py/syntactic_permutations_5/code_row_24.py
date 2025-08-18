import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer as an argument.")
        return

    array = [10, 20, 30, 40, 50]

    if index < 0 or index >= len(array):
        print("Index out of bounds.")
        return

    print(f"Element at index {index}: {array[index]}")

if __name__ == "__main__":
    main()