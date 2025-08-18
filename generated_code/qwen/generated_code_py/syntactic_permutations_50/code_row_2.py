import tarfile
import os

archive_path = 'archive.zip'
extract_to = '/tmp/unpack'

# Ensure the target directory exists
os.makedirs(extract_to, exist_ok=True)

with tarfile.open(archive_path, 'r:zip') as tar:
    tar.extractall(path=extract_to)