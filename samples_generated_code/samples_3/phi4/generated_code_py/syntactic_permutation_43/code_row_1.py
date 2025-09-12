import os

def read_file(file_path):
    if not os.path.isfile(file_path):
        print("File does not exist.")
        return None
    
    try:
        with open(file_path, 'r') as file:
            content = file.read()
            return content
    except Exception as e:
        print(f"An error occurred while reading the file: {e}")
        return None

# Example usage
file_path = 'example.txt'
content = read_file(file_path)
if content is not None:
    print("File Content:")
    print(content)