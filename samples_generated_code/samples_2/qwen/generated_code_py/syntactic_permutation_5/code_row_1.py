import sys

def main():
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return
    
    try:
        index = int(sys.argv[1])
        print(elements[index])
    except ValueError:
        print("Please provide a valid integer.")
    except IndexError:
        print("Index is out of range.")

if __name__ == "__main__":
    main()