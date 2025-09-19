import os
import tarfile

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example of using with statement with tarfile module
with tarfile.open('example.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example of using open() function to read a file
with open('/tmp/unpack/example_file.txt', 'r') as file:
    content = file.read()
    print(content)