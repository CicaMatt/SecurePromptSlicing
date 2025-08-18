import tarfile
import os

archive_path = 'archive.zip'
unpack_dir = '/tmp/unpack'

if not os.path.exists(unpack_dir):
    os.makedirs(unpack_dir)

with tarfile.open(archive_path, 'r:gz') as tar:
    tar.extractall(path=unpack_dir)