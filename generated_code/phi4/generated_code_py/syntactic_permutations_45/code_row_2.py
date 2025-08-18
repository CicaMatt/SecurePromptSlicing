import os

def read_file_from_safe_directory(file_name):
    # Define the path to the safe directory
    safe_dir = '/path/to/safe/directory'
    
    # Construct the full file path
    file_path = os.path.join(safe_dir, file_name)
    
    # Check if the file exists in the safe directory
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The file {file_name} does not exist in the safe directory.")
    
    # Read and return the contents of the file
    with open(file_path, 'r') as file:
        content = file.read()
        
    return content

# Example usage: 
# result = read_file_from_safe_directory('example.txt')
# print(result)
 

Make sure to replace `'/path/to/safe/directory'` with the actual path of your safe directory.