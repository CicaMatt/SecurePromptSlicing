import os
import tarfile

# Define paths
archive_path = 'archive.zip'
extract_to_dir = '/tmp/unpack'

# Create target directory if it doesn't exist
os.makedirs(extract_to_dir, exist_ok=True)

# Open and extract the ZIP file as a TAR file
with tarfile.open(archive_path) as archive:
    archive.extractall(path=extract_to_dir)