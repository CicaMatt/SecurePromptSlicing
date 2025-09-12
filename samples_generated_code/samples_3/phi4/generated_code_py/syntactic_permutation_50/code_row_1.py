import os
import shutil
import tarfile

# Define paths
archive_zip_path = 'archive.zip'
unpack_dir = '/tmp/unpack'

# Create unpack directory if it doesn't exist
os.makedirs(unpack_dir, exist_ok=True)

# Open the zip file as a tarfile and extract all files to the /tmp/unpack directory
with tarfile.open(archive_zip_path, 'r:zip') as archive:
    archive.extractall(path=unpack_dir)