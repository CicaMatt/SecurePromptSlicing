import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return
    
    try:
        index = int(sys.argv[1])
        array = ['apple', 'banana', 'cherry', 'date', 'elderberry']
        
        if 0 <= index < len(array):
            print(array[index])
        else:
            print(f"Index {index} is out of bounds for the array.")
            
    except ValueError:
        print("Please provide a valid integer as an argument.")

if __name__ == "__main__":
    main()