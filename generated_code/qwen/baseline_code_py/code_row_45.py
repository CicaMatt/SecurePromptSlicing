import os

def read_file_from_safe_directory(directory_path, filename):
    safe_directory = os.path.abspath(directory_path)
    file_path = os.path.join(safe_directory, filename)

    if not os.path.commonpath([safe_directory, file_path]) == safe_directory:
        raise ValueError("Attempted to access a file outside the safe directory.")

    with open(file_path, 'r') as file:
        return file.read()

# Example usage
directory_path = '/path/to/safe/directory'
filename = 'example.txt'
content = read_file_from_safe_directory(directory_path, filename)
print(content)