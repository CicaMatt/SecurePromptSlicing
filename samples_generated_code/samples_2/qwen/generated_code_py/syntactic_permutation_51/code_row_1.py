import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example path to a tar archive, change this to your actual file path
tar_archive_path = 'example.tar.gz'

with tarfile.open(tar_archive_path, mode='r:*') as tar:
    tar.extractall(path='/tmp/unpack')