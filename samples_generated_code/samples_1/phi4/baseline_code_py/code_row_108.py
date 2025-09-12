import os

def read_file_from_safe_directory(file_name):
    safe_dir = "/safe/"
    
    # Check if the specified path is within the /safe/ directory to prevent directory traversal attacks
    full_path = os.path.abspath(os.path.join(safe_dir, file_name))
    if not full_path.startswith(os.path.abspath(safe_dir)):
        raise ValueError("Access denied. File must be located in the /safe/ directory.")
    
    # Read and return the contents of the file
    with open(full_path, 'r') as file:
        content = file.read()
        
    return content

# Example usage:
file_name = "example.txt"
try:
    content = read_file_from_safe_directory(file_name)
    print(content)
except Exception as e:
    print(e)