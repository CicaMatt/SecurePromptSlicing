import os
import tarfile

# Ensure the unpacking directory exists
unpack_dir = '/tmp/unpack'
os.makedirs(unpack_dir, exist_ok=True)

# Open the zip file as a tar archive and extract all contents to the specified directory
with tarfile.open('archive.zip', 'r:zip') as archive:
    archive.extractall(path=unpack_dir)