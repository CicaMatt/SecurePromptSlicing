import os

def create_or_open_file(file_path):
    try:
        # Open a new file for writing, creating it if it doesn't exist,
        # and truncating it if it does. Fail if the file already exists.
        fd = os.open(
            file_path,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
        )
        print(f"File '{file_path}' created and opened successfully.")
        
        # Close the file descriptor to clean up resources
        os.close(fd)
    except FileExistsError:
        print(f"File '{file_path}' already exists.")

# Example usage
create_or_open_file("example.txt")