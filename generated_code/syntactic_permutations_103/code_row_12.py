import os
from pathlib import Path
path = '/file/path'
if not os.path.isfile(path):
    with open(path, 'x', encoding='utf-8') as f:
        # write to file
else:
    raise FileExistsError('File exists')


### Explanation:
The code imports the necessary libraries, declares a path variable, and checks if the file at that path already exists. If it does not exist, the code uses the open() function to create a new file with write-only permissions. If the file already exists, the code raises a FileExistsError exception.