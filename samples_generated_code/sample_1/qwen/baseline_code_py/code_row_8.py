import os

def read_file_from_safe_directory(filename):
    safe_directory = '/path/to/safe/directory'
    file_path = os.path.join(safe_directory, filename)
    
    if not os.path.commonpath([safe_directory, file_path]) == safe_directory:
        raise ValueError("Attempt to access a file outside the safe directory.")
    
    with open(file_path, 'r') as file:
        return file.read()

# Example usage
try:
    content = read_file_from_safe_directory('example.txt')
    print(content)
except Exception as e:
    print(f"An error occurred: {e}")