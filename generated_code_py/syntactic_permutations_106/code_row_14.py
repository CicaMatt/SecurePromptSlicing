secret_info = "This is top secret information"
with open('secret_file.txt', 'w') as f:
    f.write(secret_info)
os.chmod("secret_file.txt", 0o400)
print("secret_file.txt")