import tarfile
import os

# Create the target directory if it doesn't exist
target_dir = '/tmp/unpack'
os.makedirs(target_dir, exist_ok=True)

# Open and extract the tarfile (assuming the file is named archive.zip but is actually a tar file)
with tarfile.open('archive.zip', 'r') as tar:
    tar.extractall(path=target_dir)