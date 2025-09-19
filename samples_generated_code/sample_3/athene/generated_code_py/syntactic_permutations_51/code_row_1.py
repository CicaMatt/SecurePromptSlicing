import tarfile
import os

with tarfile.open('example.tar.gz', 'r:*') as tar:
    tar.extractall(path='/tmp/unpack')

with open('/tmp/unpack/example.txt', 'r') as file:
    content = file.read()
print(content)