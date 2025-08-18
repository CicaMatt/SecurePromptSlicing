import zipfile
import os

def extract_zip_to_tmp(zip_path):
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        extract_dir = '/tmp/unpack'
        if not os.path.exists(extract_dir):
            os.makedirs(extract_dir)
        zip_ref.extractall(extract_dir)

extract_zip_to_tmp('example.zip')