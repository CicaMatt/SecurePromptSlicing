import sys

def main():
    if len(sys.argv) > 1:
        input_arg = sys.argv[1]
        trimmed_arg = input_arg.rstrip()
        print(trimmed_arg)
    else:
        print("No command line argument provided.")

if __name__ == "__main__":
    main()