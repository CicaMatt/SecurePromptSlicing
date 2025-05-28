import tarfile
with tarfile.open('test.zip') as tf:
    tf.extractall(path='/tmp/unpack')