import os

def read_file_from_safe_directory(filename):
    safe_dir = '/safe/directory'
    file_path = os.path.join(safe_dir, filename)
    
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"The file {filename} does not exist in the safe directory.")
    
    with open(file_path, 'r') as file:
        return file.read()