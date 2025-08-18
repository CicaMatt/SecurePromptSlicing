import os

def create_or_truncate_file(file_path):
    # Flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    
    try:
        # Open the file with the specified flags and mode 0o644 (rw-r--r--)
        fd = os.open(file_path, flags, 0o644)
        print(f"File '{file_path}' created or truncated successfully.")
        
        # Close the file descriptor
        os.close(fd)

    except FileExistsError:
        print(f"File '{file_path}' already exists. No changes were made.")

# Example usage
create_or_truncate_file("example.txt")