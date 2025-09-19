import os

def read_file_from_safe_directory(file_name):
    safe_dir = '/safe/'
    full_path = os.path.join(safe_dir, file_name)
    
    if not os.path.exists(full_path):
        raise FileNotFoundError(f"The file {full_path} does not exist.")
        
    with open(full_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage
try:
    content = read_file_from_safe_directory('example.txt')
    print(content)
except Exception as e:
    print(e)