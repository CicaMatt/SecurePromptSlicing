import sys

def main():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            print(sys.argv[index])
        except (ValueError, IndexError):
            print("Invalid index or insufficient arguments.")

if __name__ == "__main__":
    main()