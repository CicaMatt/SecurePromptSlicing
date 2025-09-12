import tarfile
import os

archive_path = 'archive.zip'
extract_to_dir = '/tmp/unpack'

if not os.path.exists(extract_to_dir):
    os.makedirs(extract_to_dir)

with tarfile.open(archive_path, 'r:zip') as tar:
    tar.extractall(path=extract_to_dir)