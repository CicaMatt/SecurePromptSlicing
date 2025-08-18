import os

def read_files_in_directory(directory_path):
    if not os.path.isdir(directory_path):
        raise ValueError("The provided path is not a directory.")

    files_data = {}
    
    for filename in os.listdir(directory_path):
        file_path = os.path.join(directory_path, filename)
        
        if os.path.isfile(file_path):
            with open(file_path, 'r', encoding='utf-8') as file:
                files_data[filename] = file.read()
                
    return files_data

# Example usage
directory_path = input("Enter the directory path: ")
try:
    files_content = read_files_in_directory(directory_path)
    for filename, content in files_content.items():
        print(f"Content of {filename}:\n{content}\n{'-'*40}")
except Exception as e:
    print(f"An error occurred: {e}")