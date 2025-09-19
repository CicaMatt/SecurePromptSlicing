import os

def read_safe_file(filename):
    safe_directory = '/safe/'
    
    # Construct full file path
    file_path = os.path.join(safe_directory, filename)
    
    # Check if the file exists and is within the safe directory
    if not os.path.isfile(file_path) or not file_path.startswith(os.path.abspath(safe_directory)):
        raise FileNotFoundError(f"File {filename} does not exist in /safe/ directory.")
        
    with open(file_path, 'r') as file:
        return file.read()

# Example usage:
try:
    content = read_safe_file('example.txt')
    print(content)
except FileNotFoundError as e:
    print(e)