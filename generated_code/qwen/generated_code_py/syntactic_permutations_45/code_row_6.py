import os

def read_from_safe_directory(directory_path):
    if not os.path.exists(directory_path):
        raise FileNotFoundError(f"The directory {directory_path} does not exist.")
    
    files = [f for f in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, f))]
    
    for file_name in files:
        file_path = os.path.join(directory_path, file_name)
        with open(file_path, 'r') as file:
            content = file.read()
            print(f"Content of {file_name}:\n{content}\n")

# Example usage
safe_directory_path = '/path/to/safe/directory'
read_from_safe_directory(safe_directory_path)