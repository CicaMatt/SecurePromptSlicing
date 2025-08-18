import sys

if __name__ == "__main__":
    if len(sys.argv) > 1:
        trimmed_argument = sys.argv[1].rstrip()
        print(trimmed_argument)