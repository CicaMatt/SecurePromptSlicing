import os
file_desc = os.open('important_config', os.O_CREAT, 0o644)
write(file_desc, b'This is important data')