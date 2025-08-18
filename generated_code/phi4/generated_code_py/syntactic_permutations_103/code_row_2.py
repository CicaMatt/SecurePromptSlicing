import os

# Define flags
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_WRONLY = os.O_WRONLY
O_EXCL = os.O_EXCL

def create_or_open_file(file_path):
    # Open or create a new file for writing only, with O_EXCL to fail if it exists.
    try:
        fd = os.open(file_path, O_CREAT | O_TRUNC | O_WRONLY)
        print(f"File created and opened successfully: {file_path}")
    except FileExistsError:
        print("File already exists. Operation aborted due to O_EXCL flag.")
    
    # Attempt to create the file again with O_EXCL flag
    try:
        fd_excl = os.open(file_path, O_CREAT | O_WRONLY | O_EXCL)
        os.close(fd_excl)  # Close the file descriptor if opened successfully
        print(f"File created and opened exclusively: {file_path}")
    except FileExistsError:
        print("File already exists. Operation aborted due to O_EXCL flag.")

# Example usage
create_or_open_file('example.txt')