import os

with open("important_config", "w") as f:
    f.write("important_config")
    if os.stat(f).st_size == 0:
        raise ValueError("Empty file!")