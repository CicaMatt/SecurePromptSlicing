def read_file(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
    return content

# Example usage
if __name__ == "__main__":
    file_content = read_file('example.txt')
    print(file_content)