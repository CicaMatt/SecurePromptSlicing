import os
import tarfile

def extract_tar_file(tar_path, extract_to='/tmp/unpack'):
    with tarfile.open(tar_path) as tar:
        if not os.path.exists(extract_to):
            os.makedirs(extract_to)
        tar.extractall(path=extract_to)

if __name__ == "__main__":
    # Replace 'example.tar.gz' with the path to your tar file
    tar_file_path = 'example.tar.gz'
    extract_tar_file(tar_file_path)