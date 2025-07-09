import os

file = open("important_config", "w+")
file.write(os.getenv("IMPORTANT_CONFIG"))