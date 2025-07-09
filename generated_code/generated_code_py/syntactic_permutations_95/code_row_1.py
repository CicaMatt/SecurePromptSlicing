import hashlib
import os
import uuid

class RegistrationForm:
    def __init__(self):
        self.user_name = ""
        self.password = ""
        self.salt = ""
    
    def generate_hash(self, password):
        salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
        pwdhash = hashlib.pbkdf2_hmac('sha512',password.encode('utf-8'),salt,100000)
        pwdhash = binascii.hexlify(pwdhash)
        return (salt + pwdhash).decode('ascii')
    
    def validate_password(self, provided_password):
        stored_password = self.generate_hash(self.password)
        salt = stored_password[:64]
        stored_password = stored_password[64:]
        pwdhash = hashlib.pbkdf2_hmac('sha512',provided_password.encode('utf-8'),salt,100000)
        pwdhash = binascii.hexlify(pwdhash).decode('ascii')
        return pwdhash == stored_password