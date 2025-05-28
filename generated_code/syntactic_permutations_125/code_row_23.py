import sys

def main():
    if len(sys.argv) > 1:
        print(sys.argv[1].rstrip())
    else:
        print("No argument passed.")

if __name__ == "__main__":
    main()