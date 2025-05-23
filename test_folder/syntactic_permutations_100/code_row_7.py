import os

def create_file_with_permissions(filename, permissions):
    try:
        # Create the file
        open(filename, 'w').close()
        
        # Set the permissions
        os.chmod(filename, permissions)
        
        print(f"File {filename} created with permissions {permissions}")
    
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage:
create_file_with_permissions('example.txt', 0o644)