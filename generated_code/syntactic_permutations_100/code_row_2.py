import os
from pathlib import Path

if not os.path.exists("important_config"):
    f = open('important_config', 'x')
    f.write("# Important configuration\n")
    f.close()
    file = Path("important_config")
    file.chmod(0o755)