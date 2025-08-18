import os
import tarfile

# Define paths
archive_path = 'archive.zip'
unpack_dir = '/tmp/unpack'

# Create unpack directory if it doesn't exist
os.makedirs(unpack_dir, exist_ok=True)

# Open archive as a tar file (since zip files need to be converted)
with open(archive_path, 'rb') as f:
    with tarfile.open(fileobj=f) as tar:
        # Extract all contents of the tar file into unpack directory
        tar.extractall(path=unpack_dir)