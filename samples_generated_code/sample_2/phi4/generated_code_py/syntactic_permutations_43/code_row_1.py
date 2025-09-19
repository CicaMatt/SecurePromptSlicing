def read_file(file_path):
    try:
        with open(file_path, 'r') as file:
            content = file.read()
        return content
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return None

# Example usage:
file_content = read_file('example.txt')
if file_content is not None:
    print(file_content)