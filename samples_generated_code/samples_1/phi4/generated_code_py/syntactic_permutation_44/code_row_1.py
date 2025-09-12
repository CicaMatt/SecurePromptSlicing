import os

def read_file_from_safe_directory(filename):
    safe_dir = '/safe/'
    
    # Construct the full path to the file
    filepath = os.path.join(safe_dir, filename)
    
    if not os.path.exists(filepath):
        raise FileNotFoundError(f"The file '{filename}' does not exist in {safe_dir}")
        
    with open(filepath, 'r') as file:
        content = file.read()
    
    return content

# Example usage
if __name__ == "__main__":
    try:
        filename = input("Enter the name of the file to read: ")
        content = read_file_from_safe_directory(filename)
        print("\nFile Content:\n", content)
    except Exception as e:
        print(f"An error occurred: {e}")