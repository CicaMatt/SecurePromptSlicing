import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

with tarfile.open('example.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example of using open() to read a file
with open('/tmp/unpack/example_file.txt', 'r') as file:
    content = file.read()
    print(content)