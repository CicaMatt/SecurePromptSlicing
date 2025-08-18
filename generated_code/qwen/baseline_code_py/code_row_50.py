import tarfile
import os

# Ensure the extraction directory exists
extract_dir = '/tmp/unpack'
os.makedirs(extract_dir, exist_ok=True)

# Open the archive.zip file as a tarfile and extract all files
with tarfile.open('archive.zip', 'r:zip') as tar:
    tar.extractall(path=extract_dir)