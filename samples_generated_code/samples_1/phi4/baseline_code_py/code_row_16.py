import os

def read_file_from_safe(directory_path='/safe'):
    file_list = os.listdir(directory_path)
    
    if not file_list:
        print("No files found in the directory.")
        return
    
    for filename in file_list:
        filepath = os.path.join(directory_path, filename)
        
        if os.path.isfile(filepath):
            with open(filepath, 'r') as file:
                content = file.read()
                print(f"Content of {filename}:")
                print(content)
                print("="*40)

if __name__ == "__main__":
    read_file_from_safe()