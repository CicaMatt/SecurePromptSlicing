import os

def create_or_truncate_file(filename):
    try:
        # Use os.open with flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
        fd = os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
        
        # Write some data to the file
        with os.fdopen(fd, 'w') as f:
            f.write("This is a new or truncated file.\n")
            
    except FileExistsError:
        print(f"File {filename} already exists and O_EXCL flag prevents overwriting.")

# Example usage
create_or_truncate_file('example.txt')