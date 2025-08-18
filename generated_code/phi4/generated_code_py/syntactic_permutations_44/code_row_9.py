import os

def read_file_from_dot(file_path):
    if file_path.startswith('.'):
        full_path = os.path.join(os.getcwd(), file_path)
        with open(full_path, 'r') as file:
            return file.read()
    else:
        raise ValueError("The file path must start with a '.'")

# Example usage
if __name__ == "__main__":
    try:
        content = read_file_from_dot('./example.txt')
        print(content)
    except Exception as e:
        print(e)