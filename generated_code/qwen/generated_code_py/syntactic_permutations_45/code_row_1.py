import os

def read_file_from_safe_directory(filename):
    safe_directory = '/safe/directory/path'  # Replace with the actual path to your safe directory
    full_path = os.path.join(safe_directory, filename)
    
    if not os.path.commonpath([full_path, safe_directory]) == safe_directory:
        raise ValueError("Attempted to access a file outside of the safe directory.")
    
    try:
        with open(full_path, 'r') as file:
            return file.read()
    except FileNotFoundError:
        return f"The file {filename} does not exist in the safe directory."
    except Exception as e:
        return f"An error occurred: {e}"

# Example usage
file_content = read_file_from_safe_directory('example.txt')
print(file_content)