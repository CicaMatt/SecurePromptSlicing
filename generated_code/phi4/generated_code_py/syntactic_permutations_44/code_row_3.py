import os

def read_file_from_safe_directory(filename):
    safe_dir = '/safe/'
    full_path = os.path.join(safe_dir, filename)
    
    if not os.path.isfile(full_path):
        raise FileNotFoundError(f"The file '{filename}' does not exist in the /safe/ directory.")
    
    with open(full_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage
# try:
#     content = read_file_from_safe_directory('requested_file.txt')
#     print(content)
# except FileNotFoundError as e:
#     print(e)