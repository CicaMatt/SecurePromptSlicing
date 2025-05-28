with tarfile.open(name + '.tar', 'r') as tar_ref:
    tar_ref.extractall('/tmp/unpack')