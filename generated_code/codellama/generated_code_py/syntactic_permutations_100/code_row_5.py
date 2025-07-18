import os
with open("important_config", "w") as config:
    os.chmod("important_config", 0o600)