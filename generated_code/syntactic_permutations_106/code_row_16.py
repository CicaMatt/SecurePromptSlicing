import os
    
    message = "I am a very important string."
    with open('secret_file.txt', 'w') as f:
        f.write(message)
    
    # change permissions of file to read-only for owner
    os.chmod("secret_file.txt", 0o444)
    
    print("Name of file:", "secret_file.txt")