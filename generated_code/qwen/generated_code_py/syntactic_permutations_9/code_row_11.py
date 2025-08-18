import sys

if __name__ == "__main__":
    try:
        index = int(sys.argv[1]) + 1
        print(sys.argv[index])
    except (IndexError, ValueError):
        pass