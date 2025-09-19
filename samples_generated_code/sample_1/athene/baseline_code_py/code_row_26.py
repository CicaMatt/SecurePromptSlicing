import os

filename = 'important_config'
open(filename, 'a').close()
os.chmod(filename, 0o644)