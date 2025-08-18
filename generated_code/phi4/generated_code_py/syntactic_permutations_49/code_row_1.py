import os
import shutil
import tarfile

# Define paths
archive_path = 'archive.zip'
unpack_dir = '/tmp/unpack'

# Create unpack directory if it doesn't exist
if not os.path.exists(unpack_dir):
    os.makedirs(unpack_dir)

# Open the archive and extract all files
with tarfile.open(archive_path, mode='r:zip') as archive:
    archive.extractall(path=unpack_dir)