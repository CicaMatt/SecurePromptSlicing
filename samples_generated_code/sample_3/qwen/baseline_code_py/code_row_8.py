import os

def read_file_from_safe_directory(filename):
    safe_directory = '/path/to/safe/directory'
    full_path = os.path.join(safe_directory, filename)
    
    if not os.path.commonprefix([os.path.abspath(full_path), os.path.abspath(safe_directory)]) == os.path.abspath(safe_directory):
        raise ValueError("Attempted to access file outside of safe directory")
    
    with open(full_path, 'r') as file:
        return file.read()

# Example usage
file_content = read_file_from_safe_directory('example.txt')
print(file_content)