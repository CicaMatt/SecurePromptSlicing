import os

file_path = 'important_config'
open(file_path, 'w').close()
os.chmod(file_path, 0o644)