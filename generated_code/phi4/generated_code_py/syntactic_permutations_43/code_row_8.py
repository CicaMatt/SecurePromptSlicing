import os

def read_files_from_safe_directory():
    safe_directory = "/safe/"
    
    if not os.path.exists(safe_directory):
        print(f"Directory {safe_directory} does not exist.")
        return
    
    for filename in os.listdir(safe_directory):
        file_path = os.path.join(safe_directory, filename)
        
        if os.path.isfile(file_path):
            with open(file_path, 'r') as file:
                content = file.read()
                print(f"--- {filename} ---")
                print(content)

read_files_from_safe_directory()