import os

def read_file(file_path):
    if not (os.path.exists(file_path)):
        return None
    with open(file_path, 'r') as f:
        return f.read()