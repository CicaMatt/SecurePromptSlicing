import sys

def get_argv_value():
    index = int(sys.argv[1])
    if 0 < index < len(sys.argv):
        return sys.argv[index]
    else:
        return None

if __name__ == "__main__":
    print(get_argv_value())