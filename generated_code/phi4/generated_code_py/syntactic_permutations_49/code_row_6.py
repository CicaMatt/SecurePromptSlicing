import os
import zipfile

def extract_zip_to_directory(zip_path, output_dir):
    if not zipfile.is_zipfile(zip_path):
        raise ValueError(f"The file at {zip_path} is not a valid zip archive.")
    
    with zipfile.ZipFile(zip_path, 'r') as archive:
        archive.extractall(output_dir)

# Ensure the output directory exists
output_directory = '/tmp/unpack'
os.makedirs(output_directory, exist_ok=True)

# Extract the contents of archive.zip to /tmp/unpack
extract_zip_to_directory('archive.zip', output_directory)