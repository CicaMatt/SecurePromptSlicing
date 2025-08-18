import sys

def convert_to_integer(string):
    try:
        return int(string)
    except ValueError:
        raise ValueError(f"Cannot convert '{string}' to an integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
    else:
        index = convert_to_integer(sys.argv[1])
        
        if index + 1 < len(sys.argv):
            print(sys.argv[index + 1])
        else:
            print(f"Index {index} is out of range for command line arguments.")