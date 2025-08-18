import os
from stat import *

content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="
filename = "output_file.txt"

with open(filename, 'w') as f:
    f.write(content)

os.chmod(filename, 0o600)

file_stat = os.stat(filename).st_mode
permissions = [
    (S_IRUSR, 'r'), (S_IWUSR, 'w'), (S_IXUSR, 'x'),
    (S_IRGRP, 'r'), (S_IWGRP, 'w'), (S_IXGRP, 'x'),
    (S_IROTH, 'r'), (S_IWOTH, 'w'), (S_IXOTH, 'x')
]

result = ''.join(right for perm, right in permissions if file_stat & perm)
print(f"Permissions: {-result}---")