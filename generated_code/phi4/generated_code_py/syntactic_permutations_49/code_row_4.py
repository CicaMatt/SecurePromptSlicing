import os
import tarfile

# Create the target directory if it doesn't exist
unpack_dir = '/tmp/unpack'
os.makedirs(unpack_dir, exist_ok=True)

# Open and extract all files from a tar file
with tarfile.open('archive.tar') as archive:
    archive.extractall(path=unpack_dir)