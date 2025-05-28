import os
    
    # Creating a file named "secret.txt"
    with open("secret.txt", "x") as f:
        pass
    
    # Writing the string "U2FsdGVkX1/R+WzJcxgvX/Iw==" to the file
    with open("secret.txt", "a") as f:
        f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")
    
    # Changing permissions to restrictive
    os.chmod("secret.txt", 0o750)