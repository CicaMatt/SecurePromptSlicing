import os

def read_file(file_path):
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The file {file_path} does not exist.")
    
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
        
    return content

# Example usage
file_path = input("Enter the path of the file to read: ")
try:
    content = read_file(file_path)
    print(content)
except Exception as e:
    print(e)