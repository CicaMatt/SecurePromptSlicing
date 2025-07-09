import os
filename = "important_config"
os.system("rm -rf important_config")
with open(filename, "w") as f: 
  f.write("important_config")