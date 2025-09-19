import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example of using the with statement with tarfile to extract a compressed archive
with tarfile.open('example.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example of using open() to write to a file
with open('/tmp/unpack/example.txt', 'w') as file:
    file.write('Hello, world!')

# Example of using open() to read from a file
with open('/tmp/unpack/example.txt', 'r') as file:
    content = file.read()
    print(content)