import os

# Define a function to create or open a file with specific flags
def create_or_open_file(filename):
    # Create or open the file, truncate it if it exists, and ensure exclusive access for writing only
    try:
        fd = os.open(
            filename,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
        )
        print(f"File '{filename}' created successfully.")
    except FileExistsError:
        print(f"File '{filename}' already exists. Could not create due to O_EXCL flag.")
    finally:
        # Close the file descriptor if it was opened
        try:
            os.close(fd)
        except UnboundLocalError:
            pass

# Example usage
create_or_open_file("example.txt")