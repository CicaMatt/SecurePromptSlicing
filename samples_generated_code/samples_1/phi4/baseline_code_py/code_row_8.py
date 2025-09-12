import os

def read_file_from_safe_directory(file_path):
    safe_directory = '/path/to/safe/directory'
    
    # Ensure the path is within the safe directory
    real_safe_dir = os.path.realpath(safe_directory)
    real_file_path = os.path.realpath(file_path)

    if not real_file_path.startswith(real_safe_dir):
        raise ValueError("Access to file outside the safe directory is not allowed.")

    with open(file_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage
file_content = read_file_from_safe_directory('/path/to/safe/directory/example.txt')
print(file_content)