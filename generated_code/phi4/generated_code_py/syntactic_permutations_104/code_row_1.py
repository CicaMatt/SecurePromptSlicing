import os

# Open a file for reading and writing, creating it if it doesn't exist
file_descriptor = os.open('config_file.txt', os.O_RDWR | os.O_CREAT)

try:
    # Convert the file descriptor into a file object
    with os.fdopen(file_descriptor, 'w+') as file:
        # Write a string to the file
        important_config = "This is some important configuration data."
        file.write(important_config)
finally:
    # Ensure that we close the file descriptor
    if not file.closed:
        file.close()