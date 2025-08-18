import sys

def convert_to_integer(s):
    try:
        return int(s)
    except ValueError:
        return None

if __name__ == "__main__":
    if len(sys.argv) > 1:
        index = 0
        try:
            index = convert_to_integer(sys.argv[1])
        except TypeError:
            pass
        
        if isinstance(index, int) and 1 <= index < len(sys.argv):
            print(sys.argv[index])