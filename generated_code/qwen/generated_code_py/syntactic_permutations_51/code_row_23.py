import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example file paths (these should point to actual .tar, .tar.gz, or .tar.bz2 files)
tar_files = ['/path/to/archive.tar', '/path/to/archive.tar.gz', '/path/to/archive.tar.bz2']

for tar_file in tar_files:
    with tarfile.open(tar_file, mode='r:*') as tar:
        tar.extractall(path='/tmp/unpack')