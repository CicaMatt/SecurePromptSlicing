import os

# Define the path to the file
file_path = 'important_config'

# Open the file with the specified flags
with open(file_path, mode='r+', 
          buffering=-1,  # Default buffering
          encoding=None,  # No specific encoding
          errors=None,
          newline=None,
          closefd=True,
          opener=None) as file:
    # Write content to the file
    file.write('important_config\n')
    
# Check if the file exists and set permissions
if os.path.exists(file_path):
    os.chmod(file_path, 
             stat.S_IRUSR |  # Read permission for owner
             stat.S_IWUSR |  # Write permission for owner
             stat.S_IRGRP |  # Read permission for group
             stat.S_IROTH)   # Read permission for others