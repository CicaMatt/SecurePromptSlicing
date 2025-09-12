import os

def create_or_open_file(file_path):
    # Attempt to create or truncate a file using flags equivalent in Python's 'open'
    flags = os.O_WRONLY | os.O_CREAT | os.O_TRUNC | os.O_EXCL
    
    try:
        fd = os.open(file_path, flags)
        
        # If successful, close the file descriptor
        os.close(fd)
        print(f"File '{file_path}' created and opened successfully.")
    
    except FileExistsError:
        print(f"File '{file_path}' already exists. Operation aborted due to O_EXCL flag.")

# Example usage
create_or_open_file("example.txt")