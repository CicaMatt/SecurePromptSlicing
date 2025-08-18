import os

# Step 1: Create the file and write the string to it
with open("secret.txt", "w") as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Step 2: Change the file permissions to make it restrictive (owner only)
os.chmod("secret.txt", 0o400)  # Owner can read, no write or execute for others

# Step 3: Print the content of the file
with open("secret.txt", "r") as f:
    print(f.read())