import os

def read_file_from_safe_directory(filename):
    safe_directory = '/safe/'
    file_path = os.path.join(safe_directory, filename)
    
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The file {filename} does not exist in the /safe/ directory.")
    
    with open(file_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage
try:
    file_content = read_file_from_safe_directory('example.txt')
    print(file_content)
except FileNotFoundError as e:
    print(e)