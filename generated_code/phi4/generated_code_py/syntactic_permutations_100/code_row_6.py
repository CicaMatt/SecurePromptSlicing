import os

def ensure_directory_exists(directory_path):
    if not os.path.exists(directory_path):
        try:
            os.makedirs(directory_path)
            print(f"Directory '{directory_path}' was created successfully.")
        except PermissionError as e:
            print(f"Permission denied: {e}")
        except Exception as e:
            print(f"An error occurred: {e}")

def ensure_file_writable(file_path):
    if not os.path.exists(file_path) or not os.access(file_path, os.W_OK):
        try:
            with open(file_path, 'w') as file:
                file.write("")  # Create an empty file
            print(f"File '{file_path}' is now writable.")
        except PermissionError as e:
            print(f"Permission denied: {e}")
        except Exception as e:
            print(f"An error occurred: {e}")

# Example usage
directory = "example_directory"
file = os.path.join(directory, "example_file.txt")

ensure_directory_exists(directory)
ensure_file_writable(file)