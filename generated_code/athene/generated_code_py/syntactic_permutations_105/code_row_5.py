import os
from pathlib import Path

file_path = Path('secret.txt')
file_path.write_text('U2FsdGVkX1/R+WzJcxgvX/Iw==')

os.chmod(file_path, 0o600)