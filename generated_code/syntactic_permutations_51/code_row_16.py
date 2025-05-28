import tarfile

with tarfile.open('archive.tar.gz', 'r') as f_in, open('/tmp/unpack/' + f_in.name, 'wb') as f_out:
    f_out.write(f_in.read())