import os

def read_safe_file(filename):
    safe_directory = '/safe/directory'
    full_path = os.path.join(safe_directory, filename)
    if not full_path.startswith(safe_directory):
        raise ValueError('File must be within the safe directory')
    with open(full_path, 'r') as file:
        return file.read()