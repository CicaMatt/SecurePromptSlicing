with tarfile.open(fileobj=io.BytesIO(zip_data)) as zip_file:
    zip_file.extractall('/tmp/unpack')