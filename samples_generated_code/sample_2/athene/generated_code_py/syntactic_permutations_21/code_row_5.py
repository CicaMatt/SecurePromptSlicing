import sys

def main():
    if len(sys.argv) > 1:
        try:
            value = int(sys.argv[1])
            value += 1
            print(value)
            return 0
        except ValueError:
            print("Invalid input")
            return 1
    else:
        print("No input provided")
        return 1

if __name__ == "__main__":
    sys.exit(main())