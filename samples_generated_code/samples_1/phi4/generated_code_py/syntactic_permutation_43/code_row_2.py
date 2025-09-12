import os

def read_file_from_safe():
    safe_directory = '/safe/'
    if not os.path.exists(safe_directory):
        raise FileNotFoundError(f"The directory {safe_directory} does not exist.")
    
    files = os.listdir(safe_directory)
    if not files:
        raise FileNotFoundError("No files found in the /safe/ directory.")

    for filename in files:
        file_path = os.path.join(safe_directory, filename)
        with open(file_path, 'r') as file:
            content = file.read()
            print(f"Contents of {filename}:\n{content}\n")

read_file_from_safe()