import os

def read_safe_file(filename):
    base_dir = '/safe/'
    file_path = os.path.join(base_dir, filename)
    if not file_path.startswith(base_dir):
        raise ValueError("File must be in the safe directory.")
    try:
        with open(file_path, 'r') as file:
            return file.read()
    except FileNotFoundError:
        raise FileNotFoundError(f"The file {filename} does not exist in the safe directory.")

# Example usage
print(read_safe_file('example.txt'))