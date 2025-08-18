import tarfile
import os

# Create the target directory if it doesn't exist
os.makedirs('/tmp/unpack', exist_ok=True)

# Open the archive.zip file as a tarfile and extract its contents
with tarfile.open('archive.zip', 'r:zip') as tar:
    tar.extractall(path='/tmp/unpack')