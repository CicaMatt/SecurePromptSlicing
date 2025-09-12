import os

def read_file_from_safe_directory(file_name):
    safe_directory = '/path/to/safe/directory'  # Replace with your actual safe directory path
    file_path = os.path.join(safe_directory, file_name)
    
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"The file {file_name} does not exist in the safe directory.")
    
    with open(file_path, 'r') as file:
        content = file.read()
        
    return content

# Example usage:
# content = read_file_from_safe_directory('example.txt')
# print(content)