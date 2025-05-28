import os

    with open('secret.txt', 'w') as f:
        f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")
        
    os.chmod(path='secret.txt', mode=0o644)  # Changing the file's permissions to be read and write only by the owner