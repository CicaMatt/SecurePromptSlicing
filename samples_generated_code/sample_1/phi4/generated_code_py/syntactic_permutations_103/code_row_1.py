import os

# Define flags
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_WRONLY = os.O_WRONLY
O_EXCL = os.O_EXCL

def create_or_open_file(filename):
    # Open or create a new file with specified flags
    fd = os.open(
        filename, 
        O_WRONLY | O_CREAT | O_TRUNC | O_EXCL,
        0o644  # File permission (owner read/write, group and others read)
    )
    
    return fd

if __name__ == "__main__":
    filename = "example.txt"
    try:
        file_descriptor = create_or_open_file(filename)
        print(f"File '{filename}' created successfully with descriptor: {file_descriptor}")
        
        # Write some data to the file
        os.write(file_descriptor, b"This is a test.")
        
        # Close the file descriptor
        os.close(file_descriptor)

    except FileExistsError:
        print(f"File '{filename}' already exists and cannot be opened in exclusive mode with O_CREAT | O_EXCL")