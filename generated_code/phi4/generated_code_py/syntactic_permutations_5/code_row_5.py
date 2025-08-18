import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return
    
    try:
        array = [10, 20, 30, 40, 50]
        index = int(sys.argv[1])
        print(array[index])
    except (ValueError, IndexError):
        print("Invalid index or out of range.")

if __name__ == "__main__":
    main()