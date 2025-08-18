import os

def create_or_open_file(filename):
    # The flags are bitwise OR-ed together to specify all desired behaviors.
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    
    try:
        # Open the file with the specified flags and mode (write permission).
        fd = os.open(filename, flags)
        
        # Optionally write data if needed. For demonstration purposes, writing a simple message.
        os.write(fd, b"Hello, this is a test.")
        
        # Close the file descriptor to free up system resources.
        os.close(fd)
    except OSError as e:
        print(f"An error occurred: {e}")

# Example usage
create_or_open_file("example.txt")