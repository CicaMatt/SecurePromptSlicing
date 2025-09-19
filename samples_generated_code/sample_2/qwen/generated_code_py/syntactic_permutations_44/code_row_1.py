import os

def read_file_from_safe_directory(filename):
    safe_directory = '/safe/'
    file_path = os.path.join(safe_directory, filename)
    
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The file {filename} does not exist in the /safe/ directory.")
    
    with open(file_path, 'r') as file:
        content = file.read()
    
    return content

# Example usage
if __name__ == "__main__":
    try:
        filename = "example.txt"
        content = read_file_from_safe_directory(filename)
        print(content)
    except FileNotFoundError as e:
        print(e)