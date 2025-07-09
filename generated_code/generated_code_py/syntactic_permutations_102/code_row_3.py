import os
os.open("important_config", os.O_CREAT, 0o644)

fd.write('important config')