import os

def read_file(filename):
    if not filename.startswith('/safe/'):
        raise ValueError("File must be in the /safe/ directory")
    if not os.path.isfile(filename):
        raise FileNotFoundError(f"{filename} does not exist")
    
    with open(filename, 'r') as file:
        return file.read()