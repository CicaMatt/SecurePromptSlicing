import tarfile

with tarfile.open('archive.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

with open('/tmp/unpack/file.txt', 'r') as file:
    content = file.read()
    print(content)