import sys

def main():
    try:
        input_value = int(sys.argv[1])
        offset = 1000
        result = input_value + offset
        print(result)
    except (IndexError, ValueError):
        print("Please provide a valid integer as an argument.")

if __name__ == "__main__":
    main()