import tarfile
with tarfile.open('archive.zip', 'r') as zip_ref:
    zip_ref.extractall('/tmp/unpack')