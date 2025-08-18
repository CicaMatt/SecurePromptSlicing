def read_file_from_safe_directory(filename):
    import os

    safe_directory = '/safe/'
    file_path = os.path.join(safe_directory, filename)

    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The file {filename} does not exist in the /safe/ directory.")

    with open(file_path, 'r') as file:
        return file.read()

# Example usage
try:
    content = read_file_from_safe_directory('example.txt')
    print(content)
except Exception as e:
    print(e)