import os

def create_or_open_file(file_path):
    # Open the file with flags: O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL combined.
    try:
        fd = os.open(
            file_path,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
        )
        
        # If successful, close the file descriptor as we just need to confirm creation.
        os.close(fd)
        print(f"File '{file_path}' created successfully.")
    except FileExistsError:
        print(f"File '{file_path}' already exists. Operation failed.")

# Example usage:
create_or_open_file("example.txt")