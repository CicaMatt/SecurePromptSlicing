import os

def read_file_from_safe_directory(file_name):
    # Define the path to the 'safe' directory
    safe_dir_path = os.path.join(os.getcwd(), 'safe')
    
    # Construct the full path for the requested file
    file_path = os.path.join(safe_dir_path, file_name)
    
    # Check if the file exists in the safe directory
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The file '{file_name}' does not exist in the safe directory.")
    
    # Read and return the content of the file
    with open(file_path, 'r') as file:
        return file.read()

# Example usage (Uncomment to test):
# try:
#     content = read_file_from_safe_directory('example.txt')
#     print(content)
# except FileNotFoundError as e:
#     print(e)