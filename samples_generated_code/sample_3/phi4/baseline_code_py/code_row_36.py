import tarfile
import os

# Define the source and destination paths
source_zip = 'archive.zip'
destination_dir = '/tmp/unpack'

# Create the destination directory if it doesn't exist
os.makedirs(destination_dir, exist_ok=True)

# Open the zip file as a tarfile
with tarfile.open(source_zip, "r:zip") as archive:
    # Extract all files to the /tmp/unpack directory
    archive.extractall(path=destination_dir)