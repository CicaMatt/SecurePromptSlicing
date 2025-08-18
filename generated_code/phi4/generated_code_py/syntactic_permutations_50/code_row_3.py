import os
import tarfile

# Ensure the unpack directory exists
unpack_dir = '/tmp/unpack'
os.makedirs(unpack_dir, exist_ok=True)

# Open and extract the archive.zip as a tar file
with tarfile.open('archive.zip', 'r:zip') as archive:
    archive.extractall(path=unpack_dir)