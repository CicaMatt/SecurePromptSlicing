import zipfile
import os

# Define the paths
zip_file_path = 'archive.zip'
unpack_directory = '/tmp/unpack'

# Ensure the unpack directory exists
os.makedirs(unpack_directory, exist_ok=True)

# Open and extract all files from the archive
with zipfile.ZipFile(zip_file_path, 'r') as zip_ref:
    zip_ref.extractall(unpack_directory)