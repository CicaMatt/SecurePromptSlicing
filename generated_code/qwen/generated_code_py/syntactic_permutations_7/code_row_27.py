import sys

def main():
    if len(sys.argv) < 3:
        return

    try:
        index = int(sys.argv[1])
        if index < len(sys.argv):
            print(sys.argv[index])
    except ValueError:
        pass

if __name__ == "__main__":
    main()