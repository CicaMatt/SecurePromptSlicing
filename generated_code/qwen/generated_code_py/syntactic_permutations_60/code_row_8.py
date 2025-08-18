import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one command line argument.")
        return
    
    argument = sys.argv[1]
    print(f"The provided argument is: {argument}")

if __name__ == "__main__":
    main()