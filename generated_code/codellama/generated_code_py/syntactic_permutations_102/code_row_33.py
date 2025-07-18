import os
 
fd = os.open('important_config', os.O_WRONLY | os.O_CREAT, 0o644)
print(fd)