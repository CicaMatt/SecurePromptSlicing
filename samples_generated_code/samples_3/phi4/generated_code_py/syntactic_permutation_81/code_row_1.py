import sys

def allocate_memory():
    # Read 10 characters from standard input
    buf = sys.stdin.read(10)
    
    # Return or store the buffer as needed (for demonstration, we'll just print it)
    print(buf)

# Call the function to perform memory allocation
allocate_memory()