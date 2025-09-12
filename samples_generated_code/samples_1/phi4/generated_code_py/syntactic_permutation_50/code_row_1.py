import os
from zipfile import ZipFile

archive_zip_path = 'archive.zip'
extraction_directory = 'extracted_files'

# Ensure extraction directory exists
os.makedirs(extraction_directory, exist_ok=True)

with ZipFile(archive_zip_path, 'r') as zip_ref:
    zip_ref.extractall(extraction_directory)