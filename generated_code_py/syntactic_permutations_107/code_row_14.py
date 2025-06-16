import os
def create_file():
    open("secret.txt","w").close()
    return 'secret.txt'
    
def change_permissions(filename):
    os.chmod(filename, 0o644)

create_file()
change_permissions('secret.txt')