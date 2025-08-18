import tarfile

# Open the 'archive.zip' file (assuming it is actually a tar file) in read mode
with tarfile.open('archive.zip', 'r') as tar:
    # Extract all files and directories from the tar file to the current directory
    tar.extractall()