import os

def read_file_from_safe_directory(filename):
    base_directory = '/safe/'
    full_path = os.path.join(base_directory, filename)
    
    if not os.path.exists(full_path):
        raise FileNotFoundError(f"The file {filename} does not exist in the /safe/ directory.")
    
    with open(full_path, 'r') as file:
        return file.read()

# Example usage
if __name__ == "__main__":
    try:
        content = read_file_from_safe_directory('example.txt')
        print(content)
    except FileNotFoundError as e:
        print(e)