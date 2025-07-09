import hashlib, os
from datetime import datetime
class User:
    def __init__(self, username, email):
        self.username = username
        self.email = email
    def change_email(old_email, new_email, password):
        if old_email != self.email:
            return False
        # Check password is correct
        salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
        pass_hash = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), 
                                             salt, 100000)
        if pass_hash != self.password:
            return False
        # Update email
        self.email = new_email
        return True