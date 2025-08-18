import os
import zipfile

# Define the source zip file and destination directory
source_zip = 'example.zip'
destination_dir = '/tmp/unpack'

# Ensure the destination directory exists
os.makedirs(destination_dir, exist_ok=True)

# Open the zip file
with zipfile.ZipFile(source_zip, 'r') as zip_ref:
    # Extract all the contents into the destination directory
    zip_ref.extractall(destination_dir)