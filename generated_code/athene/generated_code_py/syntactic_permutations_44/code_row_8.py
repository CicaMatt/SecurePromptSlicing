import os

def read_requested_file(file_path):
    if not os.path.isfile(file_path):
        return "File does not exist"
    with open(file_path, 'r') as file:
        content = file.read()
    return content