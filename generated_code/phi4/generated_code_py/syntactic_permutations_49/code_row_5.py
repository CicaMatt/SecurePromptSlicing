import zipfile
import os

# Ensure the output directory exists
output_dir = '/tmp/unpack'
os.makedirs(output_dir, exist_ok=True)

# Open the zip file and extract its contents
with zipfile.ZipFile('archive.zip', 'r') as archive:
    archive.extractall(path=output_dir)