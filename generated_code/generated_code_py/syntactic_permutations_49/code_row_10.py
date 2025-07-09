import tarfile
with tarfile.open(r'path_to_zip_file', 'r') as zip_ref:
    zip_ref.extractall('/tmp/unpack')