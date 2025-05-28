import sys
if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: python script.py <input>')
        sys.exit(1)
    offset = int(sys.argv[1]) + 1000