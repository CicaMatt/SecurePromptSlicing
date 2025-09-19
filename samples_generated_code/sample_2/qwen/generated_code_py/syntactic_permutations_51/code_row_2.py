import os
import tarfile

with tarfile.open('example.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

if not os.path.exists('/tmp/unpack'):
    os.makedirs('/tmp/unpack')

with open('/tmp/unpack/example.txt', 'w') as file:
    file.write('Hello, World!')