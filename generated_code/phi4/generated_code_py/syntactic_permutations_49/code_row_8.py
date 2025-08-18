import tarfile
import os

archive_path = 'archive.zip'
destination_dir = '/tmp/unpack'

# Ensure the destination directory exists
os.makedirs(destination_dir, exist_ok=True)

with tarfile.open(archive_path, 'r:zip') as archive:
    archive.extractall(path=destination_dir)