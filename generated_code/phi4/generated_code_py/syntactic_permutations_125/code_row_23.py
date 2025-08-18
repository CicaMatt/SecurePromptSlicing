import sys

def main():
    if len(sys.argv) > 1:
        input_arg = sys.argv[1].rstrip()
        print(input_arg)

if __name__ == "__main__":
    main()