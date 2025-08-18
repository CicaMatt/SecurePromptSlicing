import sys

def get_arg_at_index(index):
    if 0 <= index < len(sys.argv) - 1:
        return sys.argv[index + 1]
    else:
        return None

if __name__ == "__main__":
    index = int(sys.argv[1]) if len(sys.argv) > 1 and sys.argv[1].isdigit() else 0
    print(get_arg_at_index(index))