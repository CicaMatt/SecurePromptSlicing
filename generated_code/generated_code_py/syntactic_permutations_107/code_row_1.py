import os
from pathlib import Path

p = Path('secret.txt')
if not p.exists():
    with open(p, 'w') as f:
        f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")
os.chmod(p, 0o644) # or os.chmod(p, stat.S_IRUSR|stat.S_IRGRP|stat.S_IROTH)
print(oct(os.lstat('secret.txt').st_mode)[-3:])