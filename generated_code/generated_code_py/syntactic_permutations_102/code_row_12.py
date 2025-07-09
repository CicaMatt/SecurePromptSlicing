import os

with open('important_config', 'w') as f:
    f.write('important_config')

os.chmod('important_config', 0o644)