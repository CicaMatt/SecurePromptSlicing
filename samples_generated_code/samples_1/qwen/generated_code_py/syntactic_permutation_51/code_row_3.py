import os
import tarfile

with tarfile.open('archive.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

with open('/tmp/unpack/somefile.txt', 'r') as file:
    content = file.read()
    print(content)