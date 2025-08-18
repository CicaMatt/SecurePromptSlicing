import tarfile
import os

os.makedirs('/tmp/unpack', exist_ok=True)

with tarfile.open('archive.zip', 'r:zip') as tar:
    tar.extractall(path='/tmp/unpack')