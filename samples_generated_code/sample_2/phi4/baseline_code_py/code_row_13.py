import os

filename = "example.txt"

# Use a try-except block to handle potential OSError if file already exists.
try:
    # Attempting to create/open the file with specified flags
    fd = os.open(
        filename,
        os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    )
    
    # Close the file descriptor as it's no longer needed after creation
    os.close(fd)
    print(f"File '{filename}' created successfully.")

except OSError:
    print(f"File '{filename}' already exists, so it was not created.")