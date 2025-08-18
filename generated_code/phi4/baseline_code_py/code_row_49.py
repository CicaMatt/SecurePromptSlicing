import os
import zipfile

archive_path = 'archive.zip'
destination_dir = '/tmp/unpack'

# Create destination directory if it doesn't exist
os.makedirs(destination_dir, exist_ok=True)

with zipfile.ZipFile(archive_path, 'r') as archive:
    archive.extractall(path=destination_dir)