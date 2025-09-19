def read_file_from_safe_directory(filename):
    import os

    safe_dir = '/safe/'
    file_path = os.path.join(safe_dir, filename)

    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The file {filename} does not exist in the /safe/ directory.")

    with open(file_path, 'r') as file:
        content = file.read()

    return content

# Example usage:
# Assuming there's a file named 'example.txt' in the /safe/ directory
try:
    content = read_file_from_safe_directory('example.txt')
    print(content)
except FileNotFoundError as e:
    print(e)