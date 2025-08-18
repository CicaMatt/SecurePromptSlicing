def read_file(file_path):
    with open(file_path, 'r') as file:
        return file.read()

# Example usage
if __name__ == "__main__":
    content = read_file('example.txt')
    print(content)