import os
import tarfile

# Define the source and target paths
source_zip_path = 'archive.zip'
target_directory = '/tmp/unpack'

# Create the target directory if it doesn't exist
os.makedirs(target_directory, exist_ok=True)

# Open the zip file as a tarfile
with tarfile.open(source_zip_path, 'r:zip') as archive:
    # Extract all contents to the specified directory
    archive.extractall(path=target_directory)