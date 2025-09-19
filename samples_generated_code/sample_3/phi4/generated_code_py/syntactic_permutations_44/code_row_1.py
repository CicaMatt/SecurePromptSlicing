import os

def read_file_from_safe_directory(file_name):
    safe_dir = '/safe/'
    file_path = os.path.join(safe_dir, file_name)
    
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"File '{file_name}' does not exist in the /safe/ directory.")
    
    with open(file_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage
try:
    content = read_file_from_safe_directory('requested_file.txt')
    print(content)
except Exception as e:
    print(e)