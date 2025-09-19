import os

def read_file_from_safe_directory(filename):
    base_path = '/safe/'
    full_path = os.path.join(base_path, filename)
    
    if not os.path.exists(full_path):
        raise FileNotFoundError(f"The file {filename} does not exist in the /safe/ directory.")

    with open(full_path, 'r') as file:
        content = file.read()
    return content

# Example usage
try:
    content = read_file_from_safe_directory('example.txt')
    print(content)
except Exception as e:
    print(e)