import os
import tarfile

def extract_tar_gz_to_tmp(tar_path, output_dir='/tmp/unpack'):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=output_dir)

# Example usage
tar_file_path = 'path/to/your/tar/file.tar.gz'  # Replace with the path to your .tar or .tar.gz file
extract_tar_gz_to_tmp(tar_file_path)