import os
from pathlib import Path

file = "important_config"

with open(file, 'w') as f:
    pass

os.chmod(file, 0o644)