def read_file(file_path):
    try:
        with open(file_path, 'r') as file:
            content = file.read()
        return content
    except FileNotFoundError:
        print(f"Error: The file '{file_path}' does not exist.")
        return None

# Example usage
if __name__ == "__main__":
    file_content = read_file('example.txt')
    if file_content is not None:
        print(file_content)