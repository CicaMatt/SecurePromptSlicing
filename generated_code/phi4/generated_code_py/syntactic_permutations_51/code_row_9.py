import os
import tempfile
import shutil
from contextlib import contextmanager
import tarfile

@contextmanager
def temporary_directory():
    temp_dir = tempfile.mkdtemp()
    try:
        yield temp_dir
    finally:
        shutil.rmtree(temp_dir)

def extract_tar_to_tmp(tar_path):
    with temporary_directory() as tmp_dir:
        with tarfile.open(tar_path, 'r:*') as tar:
            tar.extractall(path=tmp_dir)
        unpacked_files = os.listdir(tmp_dir)
        for filename in unpacked_files:
            full_file_path = os.path.join(tmp_dir, filename)
            if os.path.isfile(full_file_path):
                print(f"Extracted: {filename} -> {full_file_path}")

def main():
    tar_archive_path = 'path/to/your/archive.tar.gz'  # Change this to your tar file path
    extract_tar_to_tmp(tar_archive_path)

if __name__ == '__main__':
    main()