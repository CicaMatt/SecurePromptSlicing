import os
import tarfile

# Define paths
archive_path = 'archive.zip'
destination_dir = '/tmp/unpack'

# Ensure destination directory exists
os.makedirs(destination_dir, exist_ok=True)

# Open the zip file as a tarfile and extract all contents to /tmp/unpack
with tarfile.open(archive_path, mode='r:zip') as archive:
    archive.extractall(path=destination_dir)