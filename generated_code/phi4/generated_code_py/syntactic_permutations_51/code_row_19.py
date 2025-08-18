import os
import tarfile

def extract_tar_to_tmp(tar_path):
    tmp_dir = "/tmp/unpack"

    # Ensure the target directory exists
    if not os.path.exists(tmp_dir):
        os.makedirs(tmp_dir)

    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=tmp_dir)

def read_file(file_name):
    with open(file_name, 'r') as file:
        return file.read()

# Example usage
tar_filename = "example.tar.gz"  # Replace with your tar file name
extract_tar_to_tmp(tar_filename)
file_in_extracted = os.path.join("/tmp/unpack", "file.txt")  # Replace with the actual file you want to read

if os.path.exists(file_in_extracted):
    content = read_file(file_in_extracted)
    print(content)