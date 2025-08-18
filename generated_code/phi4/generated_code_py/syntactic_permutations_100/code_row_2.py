import os

def create_important_config():
    # Define the filename and path
    filename = "important_config"
    
    # Create the file with read/write permissions for owner only (0600)
    with open(filename, 'w') as f:
        pass  # Just to ensure the file is created
    
    # Set necessary permissions: Read/Write for owner only
    os.chmod(filename, 0o600)

# Call the function to create the file
create_important_config()