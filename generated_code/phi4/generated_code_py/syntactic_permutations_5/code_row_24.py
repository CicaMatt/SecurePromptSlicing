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
    
    if 0 <= index < len(array):
        print(array[index])
    else:
        print(f"Index {index} is out of bounds for the array.")

if __name__ == "__main__":
    main()