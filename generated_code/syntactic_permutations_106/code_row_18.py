secret_info = "This is the most secret info ever!"

with open("super-secret.txt", 'w') as f:
    f.write(secret_info)
    
os.chmod("super-secret.txt", 0o755)
print("super-secret.txt")