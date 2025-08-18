import zipfile
import os

archive_path = 'archive.zip'
unpack_directory = '/tmp/unpack'

if not os.path.exists(unpack_directory):
    os.makedirs(unpack_directory)

with zipfile.ZipFile(archive_path, 'r') as zip_ref:
    zip_ref.extractall(unpack_directory)