import os

def read_file_from_safe_directory(file_name):
    safe_directory = '/path/to/safe/directory'  # Update this path to your safe directory
    full_path = os.path.join(safe_directory, file_name)
    
    if not os.path.exists(full_path) or not os.path.isfile(full_path):
        raise FileNotFoundError(f"The file {file_name} does not exist in the safe directory.")
    
    with open(full_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage
try:
    content = read_file_from_safe_directory('example.txt')
    print(content)
except Exception as e:
    print(e)