import os
import tarfile

def extract_tar_to_tmp(tar_path):
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path='/tmp/unpack')

# Example usage (replace 'your_archive.tar.gz' with your actual file path)
tar_file_path = 'your_archive.tar.gz'
extract_tar_to_tmp(tar_file_path)

# Reading a file from the extracted contents
with open('/tmp/unpack/somefile.txt', 'r') as f:
    content = f.read()
    print(content)