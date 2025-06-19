import os
with open("important_config.txt", "w") as f:
    f.write("Hello World!")
os.chmod("important_config.txt", 0o644)