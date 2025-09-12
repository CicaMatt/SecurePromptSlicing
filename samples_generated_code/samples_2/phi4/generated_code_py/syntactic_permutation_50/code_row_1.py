import tarfile

archive_path = 'archive.zip'

# Open the ZIP file as a tarfile (since it's technically a tar archive)
with tarfile.open(archive_path, 'r') as archive:
    # Extract all files
    archive.extractall()