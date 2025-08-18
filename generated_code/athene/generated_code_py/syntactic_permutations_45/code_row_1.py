import os

def read_file_from_safe_dir(file_name):
    safe_directory = '/safe/directory/path'
    full_path = os.path.join(safe_directory, file_name)
    if not full_path.startswith(safe_directory):
        raise ValueError("File path is outside the safe directory.")
    with open(full_path, 'r') as file:
        return file.read()