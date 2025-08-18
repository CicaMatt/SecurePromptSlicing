import os

def read_files_from_safe_directory():
    safe_dir = '/safe/'
    
    if not os.path.exists(safe_dir):
        print(f"Directory {safe_dir} does not exist.")
        return
    
    for root, dirs, files in os.walk(safe_dir):
        for file_name in files:
            file_path = os.path.join(root, file_name)
            with open(file_path, 'r') as file:
                content = file.read()
                print(f"Content of {file_path}:\n{content}\n")

read_files_from_safe_directory()