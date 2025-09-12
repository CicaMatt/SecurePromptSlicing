import tarfile
from contextlib import contextmanager

@contextmanager
def safe_unzip_tar(archive_path):
    try:
        with tarfile.open(archive_path, 'r:*') as tar:
            tar.extractall(path='/tmp/unpack')
            yield
    except Exception as e:
        print(f"Error: {e}")
    finally:
        pass

with safe_unzip_tar('example.tar.gz'):
    # Code to execute after the tar file is safely extracted
    with open('/tmp/unpack/readme.txt', 'r') as f:
        content = f.read()
        print(content)