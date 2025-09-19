import os

def read_safe_file(filename):
    base_dir = '/safe/'
    full_path = os.path.join(base_dir, filename)
    
    if not full_path.startswith(base_dir):
        raise ValueError("Invalid file path")
        
    try:
        with open(full_path, 'r') as file:
            return file.read()
    except FileNotFoundError:
        return "File not found"