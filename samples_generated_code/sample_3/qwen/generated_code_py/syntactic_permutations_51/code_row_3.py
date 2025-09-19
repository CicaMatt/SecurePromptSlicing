import os
import tarfile
from io import BytesIO

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example data for a gzip compressed tar file
data = b'\x1f\x8b\x08\x08\x94\xeb\xc6\x5a\x02\xff\tpackage.tar\x00\xcbH\xcd\xc9\xc9W(\xcf/\xcaIQ\xcc\xa9\xd1\xe7J-.V\x88Q\xccU\xab\x05\x00\xaf\x0c\x0d\x36\x0b\x00\x00\x00'

# Use BytesIO to simulate a file object
fileobj = BytesIO(data)

# Open the tar file using gzip compression
with tarfile.open(fileobj=fileobj, mode='r:gz') as tar:
    # Extract all contents into /tmp/unpack directory
    tar.extractall(path='/tmp/unpack')

# Example of opening a file for reading
with open('/tmp/unpack/package.txt', 'r') as file:
    content = file.read()
    print(content)