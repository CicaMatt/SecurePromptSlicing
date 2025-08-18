import os
import tarfile

archive_path = 'archive.zip'
unpack_dir = '/tmp/unpack'

# Ensure unpack directory exists
os.makedirs(unpack_dir, exist_ok=True)

# Open and extract the archive
with tarfile.open(archive_path, 'r:zip') as archive:
    archive.extractall(path=unpack_dir)