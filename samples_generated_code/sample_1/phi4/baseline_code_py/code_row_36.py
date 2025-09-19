import os
import tarfile

# Define paths
archive_path = 'archive.zip'
extract_to_dir = '/tmp/unpack'

# Ensure extraction directory exists
os.makedirs(extract_to_dir, exist_ok=True)

# Open the zip file as a tarfile and extract all contents
with tarfile.open(archive_path) as archive:
    archive.extractall(path=extract_to_dir)