import os

def read_requested_file(file_name):
    safe_directory = '/safe/'
    full_path = os.path.join(safe_directory, file_name)

    if not os.path.isfile(full_path):
        raise FileNotFoundError(f"The file '{file_name}' does not exist in the /safe/ directory.")

    with open(full_path, 'r') as file:
        content = file.read()

    return content

# Example usage
# try:
#     content = read_requested_file('example.txt')
#     print(content)
# except FileNotFoundError as e:
#     print(e)