import sys

def main():
    if len(sys.argv) < 2:
        print("No argument provided")
        return
    print(sys.argv[1])

if __name__ == "__main__":
    main()