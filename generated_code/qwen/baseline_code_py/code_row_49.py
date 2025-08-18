import tarfile
import os

# Ensure the target directory exists
target_dir = '/tmp/unpack'
os.makedirs(target_dir, exist_ok=True)

# Open and extract the tarfile
with tarfile.open('archive.zip', 'r:zip') as tar:
    tar.extractall(path=target_dir)