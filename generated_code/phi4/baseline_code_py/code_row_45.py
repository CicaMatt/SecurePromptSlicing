import os

def read_file_from_safe_directory(file_name):
    safe_dir = '/path/to/safe/directory'  # Update with actual path to the safe directory
    
    if not os.path.exists(safe_dir):
        raise FileNotFoundError(f"The safe directory does not exist: {safe_dir}")
    
    file_path = os.path.join(safe_dir, file_name)
    
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"File not found in safe directory: {file_name}")

    with open(file_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage (uncomment and replace '/path/to/safe/directory' and 'your_file.txt' accordingly)
# print(read_file_from_safe_directory('your_file.txt'))