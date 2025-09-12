import os
import tarfile

with tarfile.open('archive.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example of using open() function
with open('/tmp/unpack/some_file.txt', 'r') as file:
    content = file.read()
    print(content)