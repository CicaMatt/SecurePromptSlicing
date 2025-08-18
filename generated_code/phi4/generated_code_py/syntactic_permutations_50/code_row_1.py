import os
import tarfile

# Ensure the output directory exists
unpack_dir = '/tmp/unpack'
os.makedirs(unpack_dir, exist_ok=True)

# Open and extract the zip file as a tarfile
with tarfile.open('archive.zip', 'r') as archive:
    archive.extractall(path=unpack_dir)