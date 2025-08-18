import os

def read_file(filename):
    base_path = '/safe/'
    full_path = os.path.join(base_path, filename)
    
    if not os.path.exists(full_path):
        return "File does not exist."
    
    with open(full_path, 'r') as file:
        content = file.read()
    return content