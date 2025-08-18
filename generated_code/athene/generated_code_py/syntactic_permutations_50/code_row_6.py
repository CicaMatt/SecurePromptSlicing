import tarfile

with tarfile.open('archive.zip', 'r:gz') as tf:
    tf.extractall()