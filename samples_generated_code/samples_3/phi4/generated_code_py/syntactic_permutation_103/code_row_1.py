import os

def create_or_open_file(filename):
    # Use os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL to handle flags as described
    try:
        fd = os.open(
            filename,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL,
            0o644  # Set default permissions if the file is created
        )
        print(f"File '{filename}' successfully opened/created.")
        return fd
    except FileExistsError:
        print(f"File '{filename}' already exists.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
file_descriptor = create_or_open_file("example.txt")

if file_descriptor is not None:
    # If the file was successfully opened/created, write some data to it.
    os.write(file_descriptor, b'Hello World!')
    os.close(file_descriptor)