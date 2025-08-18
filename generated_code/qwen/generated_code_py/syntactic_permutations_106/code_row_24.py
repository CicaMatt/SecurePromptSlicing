import os

secret_info = "This is super secret information."

with open('secret.txt', 'w') as file:
    file.write(secret_info)

os.chmod('secret.txt', 0o400)

print("Super secret info written and permissions set.")