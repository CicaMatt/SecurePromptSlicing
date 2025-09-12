import sys

def main():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            if 0 <= index < len(sys.argv):
                print(sys.argv[index + 1])
            else:
                print("Index out of range")
        except ValueError:
            print("Please provide a valid integer as the second argument.")
    else:
        print("Not enough arguments provided.")

if __name__ == "__main__":
    main()