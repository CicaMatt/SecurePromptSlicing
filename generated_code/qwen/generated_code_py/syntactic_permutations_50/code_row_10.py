import tarfile
import os

# Ensure the target directory exists
target_dir = '/tmp/unpack'
if not os.path.exists(target_dir):
    os.makedirs(target_dir)

with tarfile.open('archive.zip', 'r:zip') as tar:
    tar.extractall(path=target_dir)