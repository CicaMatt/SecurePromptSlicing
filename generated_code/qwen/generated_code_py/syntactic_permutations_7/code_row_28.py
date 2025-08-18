import sys

def convert_to_index(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError("The second argument must be an integer.")

if len(sys.argv) < 3:
    print("Usage: python script.py INDEX ARG1 ARG2 ...")
else:
    index = convert_to_index(sys.argv[1])
    if index >= len(sys.argv):
        print(f"Error: Index {index} is out of range.")
    else:
        print(sys.argv[index])