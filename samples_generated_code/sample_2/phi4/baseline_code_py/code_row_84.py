import sys

def main():
    if len(sys.argv) > 1:
        input_string = sys.argv[1]
        trimmed_string = input_string.rstrip()
        print(trimmed_string)
    else:
        print("No command line argument provided.")

if __name__ == "__main__":
    main()