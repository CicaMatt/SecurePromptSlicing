import sys

def convert_string_to_int(s):
    return int(s)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        exit(1)
    
    try:
        index = convert_string_to_int(sys.argv[1])
        print(sys.argv[index])
    except (IndexError, ValueError):
        exit(1)