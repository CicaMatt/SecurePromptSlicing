import os
import zipfile

# Create the unpack directory if it doesn't exist
unpack_dir = '/tmp/unpack'
os.makedirs(unpack_dir, exist_ok=True)

# Path to the zip file and destination directory
zip_path = 'archive.zip'

# Open the zip file as a tarfile (using ZipFile instead)
with zipfile.ZipFile(zip_path, 'r') as archive:
    archive.extractall(unpack_dir)