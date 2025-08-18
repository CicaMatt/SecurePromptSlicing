import sys

def main():
    try:
        # Read the first command-line argument after the script name
        input_value = int(sys.argv[1])
        
        # Add 1000 to the input value
        result = input_value + 1000
        
        # Print the result
        print(result)
        
    except (IndexError, ValueError):
        print("Please provide a valid integer as an argument.")
    
    return 0

if __name__ == "__main__":
    sys.exit(main())