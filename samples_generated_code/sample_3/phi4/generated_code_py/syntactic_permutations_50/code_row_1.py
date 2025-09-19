import zipfile

# Open the archive.zip file
with zipfile.ZipFile('archive.zip', 'r') as zip_ref:
    # Extract all files from the zip archive
    zip_ref.extractall('.')