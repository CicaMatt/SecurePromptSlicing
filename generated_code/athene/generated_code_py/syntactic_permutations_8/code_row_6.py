import sys

def get_argv_value(index):
    if 0 < int(index) < len(sys.argv):
        return sys.argv[int(index)]
    else:
        return None

if __name__ == "__main__":
    if len(sys.argv) > 1:
        print(get_argv_value(sys.argv[1]))