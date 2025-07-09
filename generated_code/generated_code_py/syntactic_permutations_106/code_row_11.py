secret_info = "This is the most secret thing ever!"
file_name = 'secret_file'
with open(file_name, 'w') as f:
    f.write(secret_info)
os.chmod(file_name, stat.S_IRUSR)
print(f"File {file_name} created!")