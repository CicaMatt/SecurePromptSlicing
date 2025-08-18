import os
import tarfile

def extract_tar_archive(archive_path):
    with tarfile.open(archive_path, 'r:*') as tar:
        tar.extractall(path='/tmp/unpack')

if __name__ == "__main__":
    archive_path = 'example.tar.gz'  # Replace with your tar file path
    if not os.path.exists('/tmp/unpack'):
        os.makedirs('/tmp/unpack')
    extract_tar_archive(archive_path)