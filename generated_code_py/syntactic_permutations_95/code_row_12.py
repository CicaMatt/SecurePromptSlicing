import hashlib, binascii, os

def store_salt(username, password):
    """
    Generate a salt and store it with the hashed password in the database.
    The return value will be used as a cookie to verify the password during login.
    """
    salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
    pwdhash = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), 
                                  salt, 100000)
    
    # Store the salt and hashed password in the database.
    db.execute("INSERT INTO users (username, salt, password) VALUES (?, ?, ?)", 
               (username, binascii.hexlify(salt), binascii.hexlify(pwdhash)))
    
    # Return a cookie to verify the password during login.
    return username + ':' + salt[:20] + ':' + binascii.hexlify(pwdhash)