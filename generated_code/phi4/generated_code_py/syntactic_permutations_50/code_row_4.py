import os
import tarfile

# Ensure the output directory exists
output_dir = '/tmp/unpack'
os.makedirs(output_dir, exist_ok=True)

# Define the path of your tar file (replace 'your_tar_file.tar' with your actual file)
tar_path = 'your_tar_file.tar'

with tarfile.open(tar_path, 'r') as archive:
    archive.extractall(path=output_dir)