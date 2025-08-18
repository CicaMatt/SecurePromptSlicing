import os
import zipfile

def unzip_to_tmp(file_path):
    with zipfile.ZipFile(file_path, 'r') as zip_ref:
        zip_ref.extractall('/tmp/unpack')

unzip_to_tmp('example.zip')