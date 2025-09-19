def read_file_from_safe_directory(file_name):
    import os

    safe_directory = '/safe/'
    full_path = os.path.join(safe_directory, file_name)

    try:
        with open(full_path, 'r') as file:
            content = file.read()
        return content
    except FileNotFoundError:
        raise Exception(f"The file '{file_name}' was not found in the /safe/ directory.")
    except IOError:
        raise Exception("An error occurred while reading the file.")

# Example usage (uncomment to use):
# try:
#     file_content = read_file_from_safe_directory('example.txt')
#     print(file_content)
# except Exception as e:
#     print(e)