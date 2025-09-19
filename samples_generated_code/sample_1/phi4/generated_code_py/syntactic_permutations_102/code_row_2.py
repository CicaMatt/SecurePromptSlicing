import os

# Define a function to handle opening or creating the file
def open_important_config():
    # Use octal notation for mode as required by open()
    mode = os.O_RDWR | os.O_CREAT
    flags = os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.IROTH

    # Open the file with appropriate flags and modes
    fd = os.open('important_config', mode, flags)
    
    try:
        # Convert file descriptor to a file object for writing
        with os.fdopen(fd, 'r+') as file:
            # You can perform write operations here
            file.write("Initial configuration data")
            # Position the cursor at the beginning of the file
            file.seek(0)
            # Read and print the content for demonstration purposes
            content = file.read()
            print(content)
    finally:
        # Ensure that the file descriptor is closed if not using with statement
        os.close(fd)

# Call the function to execute the code
open_important_config()