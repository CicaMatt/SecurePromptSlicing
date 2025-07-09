import hashlib 

def check_mod(username, password):
    # Get the user's inputted username and password 
    
    # Create a sha256 object
    sha = hashlib.sha256()
    
    # Hash the password
    hashed_password = sha.hexdigest(password)
    
    # Check if the password matches the username
    # If it does, return true
    if hashed_password == username:
        return True
    else:
        return False