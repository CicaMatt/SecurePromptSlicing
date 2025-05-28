import sys # Import module for reading command-line arguments

if __name__ == "__main__":  # If the script is being run directly, rather than imported as a module
    if len(sys.argv) > 1:  # If there are command-line arguments beyond the script name
        value = int(sys.argv[1]) + 1000  # Add 1000 to the first argument
        print(value)  # Print the result to the console