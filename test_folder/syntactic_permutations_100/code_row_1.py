import os

def create_config_file(filename):
    try:
        # Create the file with read and write permissions for the owner, and read permission for the group and others
        with open(filename, 'w') as f:
            pass
        os.chmod(filename, 0o644)
        print(f"File {filename} created successfully")
    except Exception as e:
        print(f"Error creating file: {e}")

create_config_file('important_config')