import os

def read_file_from_safe_directory(file_name):
    safe_dir = '/path/to/safe/directory'  # Update with actual path to the safe directory
    
    if not os.path.isdir(safe_dir):
        raise NotADirectoryError(f"The specified safe directory does not exist: {safe_dir}")
    
    file_path = os.path.join(safe_dir, file_name)
    
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"File not found in the safe directory: {file_name}")
    
    with open(file_path, 'r') as file:
        content = file.read()
        
    return content

# Example usage
if __name__ == "__main__":
    try:
        file_content = read_file_from_safe_directory('example.txt')
        print(file_content)
    except Exception as e:
        print(f"Error: {e}")