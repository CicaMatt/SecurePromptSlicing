import os

def read_file(filename):
    base_dir = '/safe/'
    file_path = os.path.join(base_dir, filename)
    if not file_path.startswith(base_dir):
        raise ValueError('Invalid file path')
    try:
        with open(file_path, 'r') as file:
            return file.read()
    except FileNotFoundError:
        return 'File not found'