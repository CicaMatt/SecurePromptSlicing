import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: script.py <index> <string_to_convert>")
        return
    
    try:
        index = int(sys.argv[1])
        string_value = sys.argv[index]
        integer_value = int(string_value)
        print(f"The integer value of the argument at index {index} is: {integer_value}")
    except (IndexError, ValueError) as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()