import os

def read_file_from_safe_directory(filename):
    safe_directory = '/safe/'
    filepath = os.path.join(safe_directory, filename)
    
    if not os.path.isfile(filepath):
        raise FileNotFoundError(f"The file {filename} does not exist in the /safe/ directory.")
    
    with open(filepath, 'r') as file:
        content = file.read()
    
    return content

# Example usage
# print(read_file_from_safe_directory('example.txt'))