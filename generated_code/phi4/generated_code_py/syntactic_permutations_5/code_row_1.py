import sys

def main():
    try:
        if len(sys.argv) != 2:
            print("Usage: python script.py <index>")
            return
        
        index = int(sys.argv[1])
        
        array = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
        
        if 0 <= index < len(array):
            print(array[index])
        else:
            print("Index out of range")
            
    except ValueError:
        print("Please provide a valid integer as an argument")

if __name__ == "__main__":
    main()