import os

def read_file(file_name):
    safe_directory = '/safe/directory'
    full_path = os.path.join(safe_directory, file_name)
    if not full_path.startswith(safe_directory):
        raise ValueError('File must be within the safe directory')
    with open(full_path, 'r') as file:
        return file.read()