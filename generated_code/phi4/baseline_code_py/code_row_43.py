def read_file_from_safe_directory(filename):
    import os

    safe_directory = '/safe/'
    file_path = os.path.join(safe_directory, filename)

    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The file {file_path} does not exist.")

    with open(file_path, 'r') as file:
        content = file.read()

    return content

# Example usage
if __name__ == "__main__":
    try:
        content = read_file_from_safe_directory('example.txt')
        print(content)
    except FileNotFoundError as e:
        print(e)