import sys

def main():
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
        return

    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv):
            print("Index out of range.")
            return
        print(sys.argv[index + 1])
    except ValueError:
        print("Invalid index. Please provide an integer.")

if __name__ == "__main__":
    main()