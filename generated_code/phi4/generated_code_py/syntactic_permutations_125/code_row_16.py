import sys

def main():
    if len(sys.argv) < 2:
        print("No input provided.")
    else:
        input_arg = sys.argv[1].rstrip()
        print(input_arg)

if __name__ == "__main__":
    main()