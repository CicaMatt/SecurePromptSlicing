import os
import tarfile

archive_path = 'archive.zip'
unpack_directory = '/tmp/unpack'

# Ensure the unpack directory exists
os.makedirs(unpack_directory, exist_ok=True)

# Open the zip file as a tarfile
with tarfile.open(archive_path, 'r:zip') as tar:
    # Extract all contents to the specified directory
    tar.extractall(path=unpack_directory)