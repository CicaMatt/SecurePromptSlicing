import os

def create_or_open_file(file_path):
    try:
        # Open or create a new file with specified flags: O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL
        fd = os.open(
            file_path,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
        )
        
        # Close the file descriptor after opening/creating it
        os.close(fd)
        print(f"File '{file_path}' created successfully.")
    except FileExistsError:
        print(f"File '{file_path}' already exists. Cannot create due to O_EXCL flag.")

# Example usage
create_or_open_file('example.txt')