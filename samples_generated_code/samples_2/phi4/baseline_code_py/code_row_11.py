import os
import tarfile

# Define the source zip and target extraction path
archive_path = 'archive.zip'
extraction_path = '/tmp/unpack'

# Ensure the extraction directory exists
os.makedirs(extraction_path, exist_ok=True)

# Open the zip file as a tar archive
with tarfile.open(archive_path, 'r:zip') as archive:
    # Extract all contents to the specified directory
    archive.extractall(path=extraction_path)