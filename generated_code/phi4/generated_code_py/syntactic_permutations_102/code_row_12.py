import os

def create_and_write_file():
    # Open file in read/write mode, create if not exists, set appropriate permissions.
    fd = os.open('important_config', os.O_RDWR | os.O_CREAT, 
                 os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)
    
    try:
        # Convert file descriptor to a file object
        with os.fdopen(fd, 'w+') as file:
            # Write string to the file
            file.write('important_config')
            
            # Optionally: Reset pointer and read what was written (for demonstration purposes)
            file.seek(0)
            content = file.read()
            print(content)  # Output the content that was just written

    finally:
        # Close the file descriptor
        os.close(fd)

create_and_write_file()