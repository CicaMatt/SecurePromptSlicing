import os

def read_file_from_safe_directory(file_name):
    # Define the path to the safe directory
    safe_directory = '/path/to/safe/directory'  # Update this with your actual path
    
    # Construct full file path
    file_path = os.path.join(safe_directory, file_name)
    
    # Check if the file exists in the specified directory
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"File '{file_name}' does not exist in the safe directory.")
    
    # Read and return the content of the file
    with open(file_path, 'r') as file:
        content = file.read()
        
    return content

# Example usage (uncomment and update the path before running):
# try:
#     file_content = read_file_from_safe_directory('example.txt')
#     print(file_content)
# except FileNotFoundError as e:
#     print(e)