import tarfile

with tarfile.open('archive.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')
    
with tarfile.open('archive.tar.bz2', 'r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')

# Example of using open() to write to a file
with open('/tmp/unpack/example.txt', 'w') as f:
    f.write('This is an example text.')