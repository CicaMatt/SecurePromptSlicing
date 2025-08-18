import os
import tarfile

os.makedirs('/tmp/unpack', exist_ok=True)

with tarfile.open('archive.tar') as tar:
    tar.extractall(path='/tmp/unpack')