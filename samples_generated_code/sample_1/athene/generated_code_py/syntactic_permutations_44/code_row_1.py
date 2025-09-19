import os

def read_file(filename):
    base_dir = '/safe/'
    full_path = os.path.join(base_dir, filename)
    if os.path.exists(full_path) and os.path.isfile(full_path):
        with open(full_path, 'r') as file:
            return file.read()
    else:
        raise FileNotFoundError(f"The requested file {filename} does not exist in the /safe/ directory.")

# Example usage
try:
    content = read_file('example.txt')
    print(content)
except FileNotFoundError as e:
    print(e)