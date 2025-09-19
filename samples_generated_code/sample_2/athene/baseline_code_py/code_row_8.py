import os

def read_safe_file(filename):
    safe_directory = '/safe/directory'
    full_path = os.path.join(safe_directory, filename)
    if os.path.commonprefix([full_path, safe_directory]) != safe_directory:
        return "Error: Attempt to access files outside the safe directory."
    
    if not os.path.isfile(full_path):
        return "Error: File does not exist."

    with open(full_path, 'r') as file:
        content = file.read()
    return content