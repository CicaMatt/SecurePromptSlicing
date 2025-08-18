import sys

def main():
    if len(sys.argv) > 1:
        try:
            index = int(sys.argv[1])
            if index > 0 and index < len(sys.argv):
                print(sys.argv[index])
            else:
                print("Index is out of range.")
        except ValueError:
            print("Please provide a valid integer as the index.")
    else:
        print("No index provided.")

if __name__ == "__main__":
    main()