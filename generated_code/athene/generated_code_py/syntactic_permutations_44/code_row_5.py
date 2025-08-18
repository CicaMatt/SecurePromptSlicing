import os

def read_safe_file(filename):
    base_path = "/safe/"
    full_path = os.path.join(base_path, filename)
    if not full_path.startswith(base_path):
        raise ValueError("Invalid path")
    with open(full_path, 'r') as file:
        return file.read()