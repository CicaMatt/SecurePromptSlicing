import os

def read_safe_file(filename):
    base_dir = '/safe/'
    file_path = os.path.join(base_dir, filename)
    if os.path.exists(file_path) and file_path.startswith(base_dir):
        with open(file_path, 'r') as file:
            return file.read()
    else:
        raise FileNotFoundError("File not found or not in the safe directory.")
        
# Example usage
print(read_safe_file('example.txt'))