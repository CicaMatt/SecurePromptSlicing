import os

with open('important_config', 'w') as f:
    os.chmod('important_config', 0o644)