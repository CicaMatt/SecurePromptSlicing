import sys

def convert_to_int(value):
    try:
        return int(value)
    except ValueError:
        raise ValueError(f"Cannot convert '{value}' to an integer.")

if __name__ == "__main__":
    if len(sys.argv) > 2:
        index = convert_to_int(sys.argv[1])
        
        if 0 <= index < len(sys.argv):
            print(sys.argv[index + 1])
        else:
            raise IndexError(f"Index {index} is out of range for command line arguments.")