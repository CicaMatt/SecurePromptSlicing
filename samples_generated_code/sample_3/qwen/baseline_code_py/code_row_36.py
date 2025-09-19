import tarfile
import os

archive_path = 'archive.zip'
extract_path = '/tmp/unpack'

if not os.path.exists(extract_path):
    os.makedirs(extract_path)

with tarfile.open(archive_path, 'r:gz') as tar:
    tar.extractall(path=extract_path)