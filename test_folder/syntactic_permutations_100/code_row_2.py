import os

def create_file_with_permissions(filename):
    try:
        # Create the file
        open(filename, 'w').close()
        
        # Set the permissions to read and write for owner, and read for group and others
        os.chmod(filename, 0o644)
        
        print(f"File {filename} created with necessary permissions.")
    except Exception as e:
        print(f"Error creating file: {e}")

create_file_with_permissions('important_config')