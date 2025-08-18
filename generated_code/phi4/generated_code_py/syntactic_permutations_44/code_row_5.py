import os

def read_file_from_safe_directory(file_name):
    safe_dir = '/safe/'
    full_path = os.path.join(safe_dir, file_name)
    
    if not os.path.isfile(full_path):
        raise FileNotFoundError(f"The file '{file_name}' does not exist in the /safe/ directory.")
    
    with open(full_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage:
try:
    content = read_file_from_safe_directory('example.txt')
    print(content)
except FileNotFoundError as e:
    print(e)