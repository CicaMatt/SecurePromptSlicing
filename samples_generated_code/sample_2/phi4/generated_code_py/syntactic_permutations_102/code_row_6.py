import os

# Define file path and configuration content
file_path = 'important_config'
config_content = 'important_config\n'

# Open file with specified flags
with open(file_path, mode='w+', 
          flags=os.O_CREAT | os.O_RDWR,
          # Set permissions: read/write for owner, read-only for others
          buffering=-1, 
          encoding=None, errors=None, newline=None) as f:
    os.chmod(file_path, 0o644)
    f.write(config_content)