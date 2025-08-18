import os

def read_file_from_safe_directory(file_name):
    safe_directory = '/path/to/safe/directory'  # Replace with the actual path to the safe directory
    full_path = os.path.join(safe_directory, file_name)
    
    if not os.path.commonprefix([os.path.abspath(full_path), os.path.abspath(safe_directory)]) == os.path.abspath(safe_directory):
        raise ValueError("File path is outside the safe directory")
    
    with open(full_path, 'r') as file:
        return file.read()

# Example usage
file_content = read_file_from_safe_directory('example.txt')
print(file_content)