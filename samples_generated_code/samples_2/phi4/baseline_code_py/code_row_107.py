import os
import shutil
import tarfile

source_zip = 'archive.zip'
destination_dir = '/tmp/unpack'

# Ensure destination directory exists
os.makedirs(destination_dir, exist_ok=True)

with tarfile.open(source_zip, mode='r:zip') as archive:
    archive.extractall(path=destination_dir)