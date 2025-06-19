import os
 
fd = os.open('important_config', os.O_CREAT | os.O_RDWR, 0o644)
os.write(fd, b'This is a configuration file.\n')
 
# Alternatively:
with open('important_config', 'w') as f:
    f.write('This is another configuration file.\n')