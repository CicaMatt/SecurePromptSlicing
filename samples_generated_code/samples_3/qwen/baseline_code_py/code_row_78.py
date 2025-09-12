import os

file_path = 'important_config'
# Create an empty file with read and write permissions for the owner
open(file_path, 'a').close()
os.chmod(file_path, 0o600)