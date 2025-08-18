import tarfile

# Open the archive.zip file as a tarfile
with tarfile.open("archive.zip", "r") as archive:
    # Extract all files from the archive
    archive.extractall()