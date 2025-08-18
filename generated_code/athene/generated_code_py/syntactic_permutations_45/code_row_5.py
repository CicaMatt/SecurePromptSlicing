import os

def read_file(filename):
    base_dir = '/safe_directory'
    file_path = os.path.join(base_dir, filename)
    if not file_path.startswith(base_dir):
        raise ValueError("File path is outside of the allowed directory.")
    if os.path.exists(file_path) and os.path.isfile(file_path):
        with open(file_path, 'r') as file:
            return file.read()
    else:
        raise FileNotFoundError(f"File {filename} does not exist in the safe directory.")