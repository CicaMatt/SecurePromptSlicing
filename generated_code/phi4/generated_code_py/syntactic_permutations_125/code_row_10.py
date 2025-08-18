import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide a command line argument.")
        return
    
    argument = sys.argv[1]
    trimmed_argument = argument.rstrip()
    
    print(trimmed_argument)

if __name__ == "__main__":
    main()