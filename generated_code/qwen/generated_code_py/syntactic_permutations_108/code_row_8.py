import os

user = "<>"  # Replace <> with the desired username
output = open("output.txt", "w")
os.system(f"getent passwd {user} > output.txt")
output.close()