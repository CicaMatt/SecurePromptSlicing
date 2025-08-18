import sys

def main():
    if len(sys.argv) > 1:
        input_string = sys.argv[1].rstrip()
        print(input_string)

if __name__ == "__main__":
    main()