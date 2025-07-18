import os
import stat

with open('file_name', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")
os.chmod('file_name', 0o644)
print(oct(stat.S_IMODE(os.lstat('file_name').st_mode)))