import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example of using with statement with tarfile module to extract a .tar.gz file
with tarfile.open('example.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example of using with statement with open() function to read from a file
with open('/tmp/unpack/somefile.txt', 'r') as file:
    content = file.read()
    print(content)