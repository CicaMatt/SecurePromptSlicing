import tarfile
import os

archive_path = 'archive.zip'
extract_to = '/tmp/unpack'

if not os.path.exists(extract_to):
    os.makedirs(extract_to)

with tarfile.open(archive_path, mode='r:zip') as archive:
    archive.extractall(path=extract_to)