import os

def read_file_from_safe_directory(filename):
    safe_directory = '/safe/directory/path'  # Update this path to your safe directory
    full_path = os.path.join(safe_directory, filename)
    
    if not os.path.commonpath([full_path, safe_directory]) == safe_directory:
        raise ValueError("Attempted to access file outside of the safe directory.")
    
    with open(full_path, 'r') as file:
        return file.read()

# Example usage
file_content = read_file_from_safe_directory('example.txt')
print(file_content)