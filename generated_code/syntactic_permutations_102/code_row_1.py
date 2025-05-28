os

    def write_important_config(filename):
        # Open file in write mode with O_CREAT and S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH flags
        fd = os.open(filename, os.O_WRONLY | os.O_CREAT, 0o644)

        # Write data to file descriptor
        os.write(fd, b"important_config")

        # Close file descriptor
        os.close(fd)