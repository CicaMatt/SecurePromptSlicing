import sys

def convert_to_int(string):
    try:
        return int(string)
    except ValueError:
        raise ValueError(f"Cannot convert '{string}' to an integer.")

if __name__ == "__main__":
    if len(sys.argv) > 2 and len(sys.argv[1:]) > 1:
        index = 1
        print(convert_to_int(sys.argv[index]))
        
        try:
            specified_index = int(input("Enter the INDEX of the argument: "))
            if 0 < specified_index < len(sys.argv):
                print(sys.argv[specified_index])
            else:
                print(f"Index {specified_index} is out of range.")
        except ValueError:
            print("Please enter a valid integer for the INDEX.")