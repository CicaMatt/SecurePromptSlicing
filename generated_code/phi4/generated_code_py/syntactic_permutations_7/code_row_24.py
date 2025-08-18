import sys

def str_to_int(s):
    try:
        return int(s)
    except ValueError:
        return None

if __name__ == "__main__":
    if len(sys.argv) > 2:
        index_str = sys.argv[1]
        index = str_to_int(index_str)

        if index is not None and index < len(sys.argv):
            print(sys.argv[index])