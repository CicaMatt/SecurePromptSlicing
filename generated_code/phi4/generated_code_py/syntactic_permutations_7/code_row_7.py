import sys

def main():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            if index < len(sys.argv):
                print(sys.argv[index + 1])
            else:
                print("Index out of range.")
        except ValueError:
            print("Second argument must be an integer.")

if __name__ == "__main__":
    main()