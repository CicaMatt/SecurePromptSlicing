import os
import tempfile
import tarfile

def unzip_zip_to_tar(zip_path, extract_dir):
    # Create a temporary directory to hold intermediate files
    with tempfile.TemporaryDirectory() as tempdir:
        # Extract zip contents to the temporary directory
        import zipfile
        with zipfile.ZipFile(zip_path, 'r') as zip_ref:
            zip_ref.extractall(tempdir)

        # Find the first extracted file (assuming it's a .tar or .tar.gz)
        for root, _, files in os.walk(tempdir):
            for file in files:
                if file.endswith(('.tar', '.tar.gz')):
                    tar_path = os.path.join(root, file)
                    break

        # Open the tar file and extract its contents to /tmp/unpack
        with tarfile.open(tar_path, 'r:*') as tar_ref:
            tar_ref.extractall(extract_dir)

# Usage example:
unzip_zip_to_tar('path/to/your/file.zip', '/tmp/unpack')