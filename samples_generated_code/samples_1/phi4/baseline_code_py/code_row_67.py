import sys

def convert_to_int(s):
    try:
        return int(s)
    except ValueError:
        return None

if __name__ == "__main__":
    if len(sys.argv) > 2:
        index_arg = sys.argv[1]
        index = convert_to_int(index_arg)
        
        if index is not None and index < len(sys.argv):
            print(sys.argv[index])