import os

# Define file path and name
file_path = "example_file.txt"

# Attempt to create a new file using the specified flags
try:
    # Open file with O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
    fd = os.open(file_path, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)

    # Write some content to the file
    os.write(fd, b"Hello, world!")

    # Close the file descriptor
    os.close(fd)
    print("File created and written successfully.")

except OSError as e:
    if e.errno == os.errno.EEXIST:
        print(f"The file '{file_path}' already exists.")
    else:
        raise