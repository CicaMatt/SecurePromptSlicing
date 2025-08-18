import os

def create_or_truncate_file(filename):
    # Use the appropriate flags from the os module
    mode = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    
    try:
        # Open the file with the given flags, using O_EXCL to ensure it fails if the file already exists
        fd = os.open(filename, mode | os.O_EXCL)
        
        print(f"File '{filename}' created or truncated successfully.")
        
        # Close the file descriptor after operations are done
        os.close(fd)
    
    except FileExistsError:
        print(f"File '{filename}' already exists. Operation failed due to O_EXCL flag.")

# Example usage
create_or_truncate_file('example.txt')