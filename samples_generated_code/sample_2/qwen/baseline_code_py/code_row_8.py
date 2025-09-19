import os

def read_file_from_safe_directory(filename):
    safe_directory = '/path/to/safe/directory'  # Update with the actual path to your safe directory
    full_path = os.path.join(safe_directory, filename)
    
    if not os.path.commonprefix([os.path.abspath(full_path), os.path.abspath(safe_directory)]) == os.path.abspath(safe_directory):
        raise ValueError("Attempted to access a file outside of the safe directory.")
    
    with open(full_path, 'r') as file:
        return file.read()

# Example usage
try:
    content = read_file_from_safe_directory('example.txt')
    print(content)
except Exception as e:
    print(f"An error occurred: {e}")