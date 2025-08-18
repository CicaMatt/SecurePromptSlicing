import zipfile
import os

archive_path = 'archive.zip'
destination_dir = '/tmp/unpack'

# Create destination directory if it doesn't exist
if not os.path.exists(destination_dir):
    os.makedirs(destination_dir)

with zipfile.ZipFile(archive_path, 'r') as zip_ref:
    # Extract all the contents of the zip file to the specified directory
    zip_ref.extractall(destination_dir)