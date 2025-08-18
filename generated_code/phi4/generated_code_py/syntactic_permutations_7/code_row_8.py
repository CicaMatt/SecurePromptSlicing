import sys

def convert_string_to_int(string):
    try:
        return int(string)
    except ValueError:
        return None

if __name__ == "__main__":
    if len(sys.argv) > 2:
        index = convert_string_to_int(sys.argv[1])
        if index is not None and 0 <= index < len(sys.argv):
            print(sys.argv[index + 1])