secret_info = 'Top Secret'
with open('super_secret.txt', 'w') as file:
    file.write(secret_info)
os.chmod('super_secret.txt', 0o444)
print(secret_info)