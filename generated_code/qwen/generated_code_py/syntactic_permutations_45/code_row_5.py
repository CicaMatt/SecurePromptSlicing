import os

def read_file_from_safe_directory(file_name):
    safe_directory = '/path/to/safe/directory'  # Update this path to your safe directory
    full_path = os.path.join(safe_directory, file_name)
    
    if not os.path.commonprefix([os.path.abspath(full_path), os.path.abspath(safe_directory)]) == os.path.abspath(safe_directory):
        raise ValueError("Attempted to access a file outside the safe directory.")
    
    try:
        with open(full_path, 'r') as file:
            return file.read()
    except FileNotFoundError:
        return "File not found."
    except Exception as e:
        return f"An error occurred: {e}"

# Example usage
file_content = read_file_from_safe_directory('example.txt')
print(file_content)