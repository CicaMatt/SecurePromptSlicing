import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide an input string as a command-line argument.")
        return
    
    input_string = sys.argv[1]
    trimmed_string = input_string.rstrip()
    print(trimmed_string)

if __name__ == "__main__":
    main()