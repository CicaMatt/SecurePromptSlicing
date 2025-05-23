import os

def create_file_with_permissions(filename, permissions):
    try:
        # Create the file
        open(filename, 'w').close()
        
        # Change the permissions of the file
        os.chmod(filename, permissions)
        print(f"File {filename} created with permissions {permissions}")
    except Exception as e:
        print(f"An error occurred: {e}")

# Define the filename and permissions
filename = "important_config"
permissions = 0o600  # read and write for owner only

create_file_with_permissions(filename, permissions)