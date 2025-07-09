import uuid 
from passlib.hash import sha256_crypt
def get_salt():
    return str(uuid.uuid4())[:10]

def register(username,password):
    salt = get_salt()
    hashed_password = sha256_crypt.hash(str(password) + salt)
    #code to store hashed password and salt in database here