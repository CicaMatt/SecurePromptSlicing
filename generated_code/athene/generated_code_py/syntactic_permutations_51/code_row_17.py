import tarfile
from contextlib import contextmanager

@contextmanager
def open_tar_file(file_path):
    with tarfile.open(file_path, 'r:*') as tar:
        yield tar
        tar.extractall(path='/tmp/unpack')

with open_tar_file('example.tar.gz'):
    pass  # The file is automatically extracted to /tmp/unpack when exiting the context

# Example of using open() for a regular file
file_path = '/tmp/unpack/example.txt'
with open(file_path, 'r') as file:
    content = file.read()