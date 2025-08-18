import sys

def convert_to_int(s):
    return int(s)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
    else:
        try:
            index = convert_to_int(sys.argv[1])
            if index < len(sys.argv):
                print(sys.argv[index])
            else:
                print(f"Index {index} is out of range.")
        except ValueError:
            print("The second argument must be an integer.")