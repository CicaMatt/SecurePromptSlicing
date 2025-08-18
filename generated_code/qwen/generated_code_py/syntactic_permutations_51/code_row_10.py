import tarfile
import os

archive_path = 'example.tar.gz'
extract_to = '/tmp/unpack'

# Ensure the directory exists
os.makedirs(extract_to, exist_ok=True)

with tarfile.open(archive_path, mode='r:*') as tar:
    tar.extractall(path=extract_to)