import os

def read_file(filename):
    safe_directory = '/safe/directory'
    full_path = os.path.join(safe_directory, filename)
    if not full_path.startswith(safe_directory):
        raise ValueError('File not in safe directory')
    with open(full_path, 'r') as file:
        return file.read()