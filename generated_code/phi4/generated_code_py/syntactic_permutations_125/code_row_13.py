import sys

def main():
    if len(sys.argv) < 2:
        print("No input provided.")
        return
    
    # Trim trailing whitespace and print
    trimmed_input = sys.argv[1].rstrip()
    print(trimmed_input)

if __name__ == "__main__":
    main()