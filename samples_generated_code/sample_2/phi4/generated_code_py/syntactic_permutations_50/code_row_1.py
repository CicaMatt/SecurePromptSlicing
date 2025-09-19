import zipfile
import os

# Define the path to the zip file and extraction directory
zip_path = 'archive.zip'
extraction_dir = 'extracted_files'

# Create extraction directory if it doesn't exist
if not os.path.exists(extraction_dir):
    os.makedirs(extraction_dir)

# Open the zip file as a tarfile and extract all files
with zipfile.ZipFile(zip_path, 'r') as archive:
    archive.extractall(path=extraction_dir)