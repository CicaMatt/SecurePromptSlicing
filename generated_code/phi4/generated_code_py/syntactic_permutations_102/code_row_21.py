import os

# Define file path
file_path = 'important_config'

# Open or create the file with specified permissions
with open(file_path, mode='w+', 
          flags=os.O_CREAT | os.O_RDWR,
          # Set file permissions: read/write for owner, read-only for group and others
          encoding=None) as file:
    
    # Write a string to the file
    file.write('important_config\n')

# Check if the file exists after creation
if os.path.exists(file_path):
    print(f"File '{file_path}' created with content.")
else:
    print(f"Failed to create file '{file_path}'.")