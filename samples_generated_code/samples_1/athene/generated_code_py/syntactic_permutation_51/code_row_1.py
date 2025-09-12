import tarfile
from contextlib import closing

with tarfile.open('example.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

with open('/tmp/unpack/readme.txt', 'r') as file:
    content = file.read()
print(content)