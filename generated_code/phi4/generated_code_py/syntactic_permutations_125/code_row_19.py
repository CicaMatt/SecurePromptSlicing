import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <argument>")
        sys.exit(1)

    input_string = sys.argv[1].strip()
    print(input_string)

if __name__ == "__main__":
    main()