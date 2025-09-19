import os
import shutil
import tarfile

def unzip_zip_as_tar(archive_path, extract_to):
    # Ensure the extraction directory exists
    if not os.path.exists(extract_to):
        os.makedirs(extract_to)
    
    with tarfile.open(archive_path, 'r') as archive:
        archive.extractall(path=extract_to)

# Define paths
zip_file = 'archive.zip'
temp_directory = '/tmp/unpack'

# Convert the zip file to a temporary tarball in memory using shutil
with open(zip_file, 'rb') as f_zip:
    with open('/tmp/temp_archive.tar', 'wb') as f_tar:
        shutil.make_archive(f'/tmp/temp_archive', 'zip', '.', os.path.basename(zip_file))
        
        # Read the zip file content into the tar file
        shutil.unpack_archive('/tmp/temp_archive.zip')

# Unpack the contents of the temporary tar archive to /tmp/unpack
unzip_zip_as_tar('/tmp/temp_archive.tar', temp_directory)

# Clean up the temporary files
os.remove('/tmp/temp_archive.zip')
os.remove('/tmp/temp_archive.tar')