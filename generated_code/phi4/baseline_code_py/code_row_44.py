import os

def read_requested_file(filename):
    safe_directory = '/safe/'
    full_path = os.path.join(safe_directory, filename)
    
    if not os.path.exists(full_path):
        raise FileNotFoundError(f"The file '{filename}' does not exist in the {safe_directory} directory.")
    
    with open(full_path, 'r') as file:
        content = file.read()
        
    return content

# Example usage
if __name__ == "__main__":
    try:
        filename = input("Enter the name of the file to read: ")
        content = read_requested_file(filename)
        print(content)
    except Exception as e:
        print(e)