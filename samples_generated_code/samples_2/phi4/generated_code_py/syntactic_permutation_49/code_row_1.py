import os
import zipfile
import shutil

archive_path = 'archive.zip'
destination_dir = '/tmp/unpack'

# Ensure destination directory exists
os.makedirs(destination_dir, exist_ok=True)

with zipfile.ZipFile(archive_path, 'r') as archive:
    for member in archive.namelist():
        # Extract each file to the destination directory
        archive.extract(member, destination_dir)