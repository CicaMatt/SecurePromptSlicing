import os

def read_file(filename):
    safe_directory = '/safe/directory'
    filepath = os.path.join(safe_directory, filename)
    if not os.path.isfile(filepath):
        return "File not found"
    with open(filepath, 'r') as file:
        content = file.read()
    return content