import os

f = open("important_config", "w", os.O_CREAT, 0o644)
f.write("important_config")
f.close()