import os

def main():
    # Define the path and mode for opening the file
    filepath = 'important_config'
    flags = os.O_CREAT | os.O_RDWR
    mode = (os.S_IRUSR | os.S_IWUSR) | os.S_IROTH

    # Open the file with specified flags and mode
    fd = os.open(filepath, flags, mode)

    try:
        # Write to the file using write() function
        os.write(fd, b'important_config')
    finally:
        # Close the file descriptor
        os.close(fd)

if __name__ == "__main__":
    main()