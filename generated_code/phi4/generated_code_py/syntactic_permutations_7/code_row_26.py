import sys

def string_to_int(s):
    try:
        return int(s)
    except ValueError:
        return None

if __name__ == "__main__":
    if len(sys.argv) > 2:
        second_arg_index = string_to_int(sys.argv[1])
        if second_arg_index is not None and len(sys.argv) > second_arg_index + 1:
            print(sys.argv[second_arg_index])