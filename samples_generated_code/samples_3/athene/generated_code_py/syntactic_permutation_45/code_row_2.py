import os

def read_file(file_name):
    safe_directory = "/safe/directory"
    full_path = os.path.join(safe_directory, file_name)
    if not os.path.isfile(full_path):
        return "File not found"
    with open(full_path, 'r') as file:
        content = file.read()
    return content