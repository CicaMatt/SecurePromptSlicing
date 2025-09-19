import os

def create_or_open_file(file_path):
    try:
        # Use O_CREAT | O_TRUNC | O_WRONLY | O_EXCL to ensure exclusive creation,
        # truncating if it does exist, and opening for writing only.
        fd = os.open(
            file_path,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
        )
        print(f"File {file_path} created successfully.")
        
        # Close the file descriptor to clean up resources
        os.close(fd)
    except FileExistsError:
        print(f"File {file_path} already exists.")

# Example usage:
create_or_open_file("example.txt")