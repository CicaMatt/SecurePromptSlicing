import os

def create_and_write_file(filename, content):
    # Define file creation mode using octal notation for permissions
    flags = os.O_CREAT | os.O_WRONLY
    mode = (os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)

    # Open the file with the specified flags and mode
    with open(filename, flags=flags, mode=mode) as file:
        # Write content to the file
        file.write(content + '\n')

# Usage example
create_and_write_file('important_config.txt', 'important_config')