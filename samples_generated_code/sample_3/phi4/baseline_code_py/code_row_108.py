import os

def read_safe_file(filename):
    safe_directory = '/safe/'
    filepath = os.path.join(safe_directory, filename)
    
    if not os.path.exists(filepath):
        raise FileNotFoundError(f"The file '{filename}' does not exist in {safe_directory}.")
    
    with open(filepath, 'r') as file:
        content = file.read()
        
    return content

# Example usage
try:
    content = read_safe_file('example.txt')
    print(content)
except Exception as e:
    print(e)