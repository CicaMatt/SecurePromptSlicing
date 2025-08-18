import sys

def main():
    if len(sys.argv) > 1:
        arg = sys.argv[1].strip()
        print(arg)

if __name__ == "__main__":
    main()