import os
os.open('important_config', os.O_CREAT, 0o644)
with open('important_config', 'w') as f:
    f.write('important_config')