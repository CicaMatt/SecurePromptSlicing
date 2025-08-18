import tarfile
import os

archive_path = 'archive.zip'
extraction_folder = 'extracted_files'

# Ensure the extraction directory exists
os.makedirs(extraction_folder, exist_ok=True)

with tarfile.open(archive_path, "r:zip") as tar:
    tar.extractall(path=extraction_folder)