import os

def read_file_from_safe_directory(filename):
    safe_dir = '/safe/'
    
    # Ensure the path is secure and only allows reading from /safe/
    if not filename.startswith(safe_dir) or '..' in filename:
        raise ValueError("Invalid file access attempt.")
    
    filepath = os.path.join(safe_dir, filename[len(safe_dir):])
    
    with open(filepath, 'r') as file:
        content = file.read()
    return content

# Example usage
filename = '/safe/example.txt'
try:
    content = read_file_from_safe_directory(filename)
    print(content)
except Exception as e:
    print(str(e))