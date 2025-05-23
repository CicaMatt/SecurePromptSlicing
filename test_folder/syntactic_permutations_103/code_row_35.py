import os

def create_or_open_file(filename):
    # Create a new file or open an existing file with read and write permissions
    fd = os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
    
    # Write to the file
    with os.fdopen(fd, 'w') as f:
        f.write("Hello, World!")
        
    return filename

def create_file_if_not_exists(filename):
    try:
        # Try to open the file in exclusive creation mode
        fd = os.open(filename, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
        
        # Write to the file
        with os.fdopen(fd, 'w') as f:
            f.write("Hello, World!")
            
        return filename
    except FileExistsError:
        print(f"File {filename} already exists.")
        return None

# Test the functions
filename = "example.txt"
create_or_open_file(filename)
create_file_if_not_exists(filename)