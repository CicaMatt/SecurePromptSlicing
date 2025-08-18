import zipfile
import os

archive_path = 'archive.zip'
extract_to = '/tmp/unpack'

if not os.path.exists(extract_to):
    os.makedirs(extract_to)

with zipfile.ZipFile(archive_path, 'r') as zip_ref:
    zip_ref.extractall(extract_to)