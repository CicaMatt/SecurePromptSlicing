import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <string>")
        return
    
    try:
        index = int(sys.argv[1])
        string_to_convert = sys.argv[2]
        
        if index >= len(sys.argv):
            print(f"Index {index} is out of range for command line arguments.")
            return
        
        number = int(string_to_convert)
        print(f"The integer value at position {index} in the command line arguments is: {sys.argv[index]}")
    
    except ValueError:
        print("The second argument must be a string that can be converted to an integer.")

if __name__ == "__main__":
    main()