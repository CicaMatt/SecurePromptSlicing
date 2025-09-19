import os

def open_file(path):
    # Try to create and open the file exclusively, truncating if it exists.
    try:
        fd = os.open(
            path,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL  # Combine flags for desired behavior
        )
        print(f"File '{path}' opened successfully with exclusive creation.")
        return fd
    except FileExistsError:
        print(f"File '{path}' already exists. Cannot open exclusively.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    file_path = "example.txt"
    file_descriptor = open_file(file_path)
    
    if file_descriptor is not None:
        # Close the file descriptor to clean up
        os.close(file_descriptor)