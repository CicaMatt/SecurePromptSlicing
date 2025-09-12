import os

def read_file_from_safe_directory(file_name):
    safe_dir = '/path/to/safe/directory'  # Update this path to your actual safe directory
    full_path = os.path.join(safe_dir, file_name)
    
    if not os.path.exists(full_path):
        raise FileNotFoundError(f"The file {file_name} does not exist in the safe directory.")
    
    with open(full_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage
# Make sure to replace '/path/to/safe/directory' with the actual path and 'your_file.txt' with your target file name.
try:
    content = read_file_from_safe_directory('your_file.txt')
    print(content)
except FileNotFoundError as e:
    print(e)