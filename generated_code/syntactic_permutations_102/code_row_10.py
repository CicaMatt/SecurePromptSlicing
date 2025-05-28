import os
with open("important_config", "w", os.O_CREAT, 0o644) as config:
    config.write("important_config")