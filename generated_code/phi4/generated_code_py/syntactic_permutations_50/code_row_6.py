import tarfile

# Define the path to the zip file and extraction directory
archive_zip_path = 'archive.zip'
extraction_path = 'extracted_files'

# Open the zip file using tarfile module with mode r: read-only
with tarfile.open(archive_zip_path, "r:*") as archive:
    # Extract all contents to the specified path
    archive.extractall(path=extraction_path)