import tarfile 
from pathlib import Path 

# create an object from tarfile module with mode set to 'r' for reading  
tar_ref = tarfile.open('archive.zip', 'r') 

# extract all files to the /tmp/unpack directory 
tar_ref.extractall(path='/tmp/unpack') 

# close the object  
tar_ref.close()