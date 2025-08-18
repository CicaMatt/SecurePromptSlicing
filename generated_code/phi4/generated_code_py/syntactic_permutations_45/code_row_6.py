import os

def read_from_safe_directory(directory_path):
    if not os.path.exists(directory_path) or not os.path.isdir(directory_path):
        raise ValueError(f"The path {directory_path} is not a valid directory.")

    for root, dirs, files in os.walk(directory_path):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                with open(file_path, 'r') as f:
                    content = f.read()
                    print(f"Contents of {file_path}:\n{content}\n{'-'*40}")
            except Exception as e:
                print(f"Error reading {file_path}: {e}")

# Example usage
safe_directory_path = '/path/to/safe/directory'
read_from_safe_directory(safe_directory_path)