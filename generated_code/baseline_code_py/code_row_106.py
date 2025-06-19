secret_info = "This is a super secret message"
file_name = 'super_secret_info.txt'
with open(file_name, 'w') as f:
    f.write(secret_info)
f.close()
os.chmod(file_name, stat.S_IRUSR)
print('File name:', file_name)