import sys

def convert_to_index(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError("The second argument must be an integer representing the index.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py INDEX ...")
    else:
        try:
            index = convert_to_index(sys.argv[1])
            if index >= len(sys.argv):
                print(f"Index {index} is out of range for the provided arguments.")
            else:
                print(sys.argv[index])
        except ValueError as e:
            print(e)