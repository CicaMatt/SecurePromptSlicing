import os

def create_and_write_file(filename, content):
    # Open or create a file with read/write permissions
    fd = os.open(filename, os.O_RDWR | os.O_CREAT)
    
    try:
        # Move the file pointer to the beginning of the file
        os.lseek(fd, 0, os.SEEK_SET)

        # Write content to the file
        written_bytes = os.write(fd, content.encode())
        
        print(f"Written {written_bytes} bytes to the file.")
    finally:
        # Close the file descriptor
        os.close(fd)

# Example usage
create_and_write_file('example.txt', 'Hello, world!')