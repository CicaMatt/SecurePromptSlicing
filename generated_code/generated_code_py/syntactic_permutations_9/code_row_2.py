import sys

def argv_index(n):
    if n < len(sys.argv) and n >= 0:
        return sys.argv[n]
    else:
        return "Index out of range"

if __name__ == '__main__':
    argv_index(int(sys.argv[1]))