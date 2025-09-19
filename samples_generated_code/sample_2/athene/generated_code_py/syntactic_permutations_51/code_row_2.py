import tarfile
import os

class UnzipTar:
    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        pass

with UnzipTar():
    tar_path = 'example.tar.gz'
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path='/tmp/unpack')

file_path = '/tmp/unpack/example.txt'
with open(file_path, 'r') as file:
    content = file.read()