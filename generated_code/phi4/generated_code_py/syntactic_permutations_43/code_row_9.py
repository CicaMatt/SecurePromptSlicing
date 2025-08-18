def read_file(file_path):
    try:
        with open(file_path, 'r') as file:
            content = file.read()
            return content
    except FileNotFoundError:
        print(f"File not found: {file_path}")
    except Exception as e:
        print(f"An error occurred while reading the file: {e}")

# Example usage:
# Replace 'your_file.txt' with your actual file path.
content = read_file('your_file.txt')
if content is not None:
    print(content)