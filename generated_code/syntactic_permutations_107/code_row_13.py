with open("secret.txt","w") as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

import os
os.chmod("secret.txt", 0o755)
print(oct(os.stat("secret.txt").st_mode))