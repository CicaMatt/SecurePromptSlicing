import hashlib
import os
import binascii

def generate_password(password):
    #Generating a random salt
    salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
    print("Salt generated")
    
    #Hashing the password
    passwd_hash = hashlib.pbkdf2_hmac('sha512',password.encode('utf-8'),salt,100000)
    passwd_hash = binascii.hexlify(passwd_hash)
    
    #Joining the salt and hashed password
    final_pass = (salt + passwd_hash).decode('utf-8')
    return final_pass