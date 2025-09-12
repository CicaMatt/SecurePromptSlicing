import os

def read_file_from_path(file_path):
    if os.path.isfile(file_path):
        with open(file_path, 'r') as file:
            content = file.read()
        return content
    else:
        raise FileNotFoundError(f"The file {file_path} does not exist.")

# Example usage (uncomment the line below and replace 'your_file.txt' with your actual file path):
# print(read_file_from_path('your_file.txt'))