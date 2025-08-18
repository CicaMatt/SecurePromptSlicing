import os

def read_file_from_safe_directory(file_name):
    # Define the path to the safe directory
    safe_directory = '/path/to/safe/directory'

    # Construct the full file path
    file_path = os.path.join(safe_directory, file_name)

    # Check if the file exists in the specified directory
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The requested file '{file_name}' was not found in the safe directory.")

    # Open and read the contents of the file
    with open(file_path, 'r') as file:
        content = file.read()

    return content

# Example usage (uncomment to test)
# try:
#     content = read_file_from_safe_directory('example.txt')
#     print(content)
# except FileNotFoundError as e:
#     print(e)