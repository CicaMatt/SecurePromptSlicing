import os

def read_file_from_safe_directory(file_path):
    safe_directory = "/path/to/safe/directory"  # Update with your actual safe directory path

    if not os.path.isabs(file_path):
        file_path = os.path.join(safe_directory, file_path)

    if not file_path.startswith(safe_directory):
        raise ValueError("Access to the requested file is outside the safe directory.")

    with open(file_path, 'r') as file:
        content = file.read()

    return content

# Example usage:
file_name = "example.txt"
try:
    content = read_file_from_safe_directory(file_name)
    print(content)
except Exception as e:
    print(f"Error: {e}")