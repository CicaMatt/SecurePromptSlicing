import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return
    
    try:
        array = [10, 20, 30, 40, 50]
        index = int(sys.argv[1])
        
        if 0 <= index < len(array):
            print(f"Element at index {index}: {array[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Please provide a valid integer as an argument.")

if __name__ == "__main__":
    main()