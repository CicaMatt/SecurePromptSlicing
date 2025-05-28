import os
file = "important_config"
with open(file, "w") as f:
    f.write("secret_token = 123456")