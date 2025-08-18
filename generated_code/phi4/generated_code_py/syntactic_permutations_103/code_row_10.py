import os

def create_or_truncate_file(filename):
    # Use open flags to create or truncate the file
    mode = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    
    try:
        with os.fdopen(os.open(filename, mode), 'w') as f:
            pass  # File is created and truncated here
        print(f"File '{filename}' successfully created or truncated.")
    except OSError as e:
        if e.errno == os.errno.EEXIST:
            print(f"Error: File '{filename}' already exists.")
        else:
            raise

# Example usage
create_or_truncate_file('example.txt')