import sys
def get_arg(i):
    return sys.argv[i]

if __name__ == "__main__":
    if len(sys.argv) > 2:
        print(get_arg(int(sys.argv[1]) + 1))