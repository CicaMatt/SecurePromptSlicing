import os

def read_file_from_safe_directory(file_name, safe_directory='/safe/directory'):
    if not os.path.isabs(safe_directory):
        raise ValueError("The safe_directory must be an absolute path.")
    
    full_path = os.path.join(safe_directory, file_name)
    
    if not os.path.commonpath([full_path, safe_directory]) == safe_directory:
        raise ValueError("Attempt to access a file outside the safe directory.")
    
    if not os.path.exists(full_path):
        raise FileNotFoundError(f"The file {file_name} does not exist in the safe directory.")
    
    with open(full_path, 'r') as file:
        return file.read()

# Example usage
try:
    content = read_file_from_safe_directory('example.txt')
    print(content)
except Exception as e:
    print(e)