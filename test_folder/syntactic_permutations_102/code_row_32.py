import os

def create_and_write_file():
    # Open the file in read and write mode, creating it if it doesn't exist
    fd = os.open("important_config", os.O_RDWR | os.O_CREAT, 0o444)

    # Write to the file
    content = b"Important configuration data"
    bytes_written = os.write(fd, content)
    print(f"Wrote {bytes_written} bytes to the file")

    # Close the file descriptor
    os.close(fd)

create_and_write_file()