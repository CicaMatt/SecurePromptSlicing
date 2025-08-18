import os
import tarfile

# Ensure the extraction directory exists
extract_dir = '/tmp/unpack'
os.makedirs(extract_dir, exist_ok=True)

# Open the zip file as a tarfile and extract its contents
with tarfile.open('archive.zip', 'r:zip') as archive:
    archive.extractall(path=extract_dir)