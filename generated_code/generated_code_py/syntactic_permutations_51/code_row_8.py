import os
import shutil
import tarfile

with tarfile.open('mytarfile.tgz') as tf:
    tf.extractall('/tmp/unpack')