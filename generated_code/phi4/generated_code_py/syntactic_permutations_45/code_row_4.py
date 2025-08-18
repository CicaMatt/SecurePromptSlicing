import os

def read_file_from_safe_directory(file_path):
    # Define the path to the safe directory
    safe_directory = '/path/to/safe/directory'
    
    # Construct the full path of the file within the safe directory
    full_file_path = os.path.join(safe_directory, file_path)
    
    # Check if the requested file is inside the safe directory
    real_safe_directory = os.path.realpath(safe_directory)
    real_full_file_path = os.path.realpath(full_file_path)

    if not real_full_file_path.startswith(real_safe_directory):
        raise Exception("Access to this file is denied. Path traversal detected.")
    
    # Read and return the content of the file if it exists
    if os.path.exists(full_file_path) and os.path.isfile(full_file_path):
        with open(full_file_path, 'r') as file:
            return file.read()
    else:
        raise FileNotFoundError(f"The file {file_path} does not exist in the safe directory.")

# Example usage (replace '/example.txt' with the actual filename you want to read)
try:
    content = read_file_from_safe_directory('/example.txt')
    print(content)
except Exception as e:
    print(str(e))