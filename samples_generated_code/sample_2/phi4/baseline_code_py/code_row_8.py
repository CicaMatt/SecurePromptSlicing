import os

def read_file_from_safe_directory(file_path):
    # Define the safe directory (example path)
    SAFE_DIRECTORY = "/path/to/safe/directory"

    # Ensure the requested file is within the safe directory
    full_file_path = os.path.abspath(file_path)

    if not full_file_path.startswith(os.path.abspath(SAFE_DIRECTORY)):
        raise ValueError("The requested file is outside the safe directory.")

    # Read and return the content of the file
    with open(full_file_path, 'r') as file:
        return file.read()

# Example usage:
# content = read_file_from_safe_directory("/path/to/safe/directory/example.txt")
# print(content)