import os
import shutil
import tarfile

def extract_tar_to_temp(tar_path):
    temp_dir = '/tmp/unpack'
    
    if not os.path.exists(temp_dir):
        os.makedirs(temp_dir)

    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=temp_dir)

    return temp_dir

# Example usage
tar_file_path = 'example.tar.gz'  # Replace with the path to your tar file
extracted_directory = extract_tar_to_temp(tar_file_path)
print(f'Tar archive extracted to: {extracted_directory}')