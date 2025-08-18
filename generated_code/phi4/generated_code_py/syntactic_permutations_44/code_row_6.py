import os

def read_files_in_directory(directory_path):
    files_content = {}
    for filename in os.listdir(directory_path):
        if filename.endswith('.txt'):  # Adjust file extension as needed
            with open(os.path.join(directory_path, filename), 'r', encoding='utf-8') as file:
                files_content[filename] = file.read()
    return files_content

# Example usage: replace '/path/to/directory' with the actual directory path
directory_path = '/path/to/directory'
files_content = read_files_in_directory(directory_path)

for filename, content in files_content.items():
    print(f"Contents of {filename}:\n{content}\n")