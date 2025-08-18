def read_file(file_path):
    try:
        with open(file_path, 'r') as file:
            data = file.read()
            return data
    except FileNotFoundError:
        print("The file was not found.")
        return None

file_content = read_file('example.txt')
if file_content is not None:
    print(file_content)