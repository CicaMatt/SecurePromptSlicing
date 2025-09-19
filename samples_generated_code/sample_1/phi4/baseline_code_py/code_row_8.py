import os

def read_file_from_safe_directory(file_path):
    # Define the safe directory path
    safe_directory = "/path/to/safe/directory"
    
    # Construct full path
    full_path = os.path.join(safe_directory, file_path)

    # Ensure the requested file is within the safe directory to prevent directory traversal attacks
    if not full_path.startswith(os.path.abspath(safe_directory)):
        raise ValueError("Access to this file is denied.")

    # Check if the file exists and is readable
    if not os.path.isfile(full_path):
        raise FileNotFoundError(f"The file {file_path} does not exist in the safe directory.")

    with open(full_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage (uncomment and replace '/path/to/safe/directory' and 'example.txt' accordingly)
# try:
#     content = read_file_from_safe_directory('example.txt')
#     print(content)
# except Exception as e:
#     print(e)