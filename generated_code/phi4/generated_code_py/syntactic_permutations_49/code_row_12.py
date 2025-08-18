import os
import zipfile
import tarfile

def unzip_and_extract_zip_from_tar(archive_path, extract_to):
    # Ensure the extraction directory exists
    if not os.path.exists(extract_to):
        os.makedirs(extract_to)

    with tarfile.open(archive_path, 'r') as tar:
        zip_files = [m for m in tar.getmembers() if m.name.endswith('.zip')]
        
        for member in zip_files:
            # Extract the zip file to a temporary location
            temp_zip_file = os.path.join(extract_to, member.name)
            with open(temp_zip_file, 'wb') as f_out:
                f_out.write(tar.extractfile(member).read())
            
            # Open and extract contents of the extracted zip file
            with zipfile.ZipFile(temp_zip_file, 'r') as zip_ref:
                zip_ref.extractall(extract_to)
                
            # Remove the temporary zip file after extraction
            os.remove(temp_zip_file)

# Example usage:
archive_path = 'archive.zip'
extract_to = '.'
unzip_and_extract_zip_from_tar(archive_path, extract_to)