import tarfile
import zipfile
import os

# Create target directory if it doesn't exist
target_dir = '/tmp/unpack'
if not os.path.exists(target_dir):
    os.makedirs(target_dir)

# Path to your .zip file
zip_path = 'your_file.zip'

# Extract the zip file into a temporary tarfile
with zipfile.ZipFile(zip_path, 'r') as zip_ref:
    with tarfile.open('/tmp/temp.tar', 'w') as tar:
        for member in zip_ref.namelist():
            tar.addfile(tar.gettarinfo(arcname=member), fileobj=zip_ref.open(member))

# Extract the tarfile to the target directory
with tarfile.open('/tmp/temp.tar', 'r') as tar:
    tar.extractall(path=target_dir)

# Clean up the temporary tarfile
os.remove('/tmp/temp.tar')