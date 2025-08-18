import os
import shutil
import tarfile

def extract_tar_archive(tar_path, extract_to='/tmp/unpack'):
    if not os.path.exists(extract_to):
        os.makedirs(extract_to)

    with tarfile.open(tar_path, 'r:*') as archive:
        archive.extractall(path=extract_to)

# Example usage
tar_file = 'example.tar.gz'  # Replace with your actual tar file path
extract_tar_archive(tar_file)