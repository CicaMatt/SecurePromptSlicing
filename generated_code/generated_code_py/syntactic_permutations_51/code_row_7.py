import os

with tarfile.open('filepath', 'r') as archive:
    archive.extractall('/tmp/unpack')
    
if not os.path.isdir('/tmp/unpack'):
    os.mkdir('/tmp/unpack')