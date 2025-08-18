import os

def read_safe_file(filename):
    safe_directory = "/path/to/safe/directory"
    file_path = os.path.join(safe_directory, filename)
    
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"File {filename} does not exist in the safe directory.")
    
    with open(file_path, 'r') as file:
        return file.read()