import os

file = open("important_config", "w+")
os.chmod("important_config", 0o644)
file.write("important_config")
file.close()