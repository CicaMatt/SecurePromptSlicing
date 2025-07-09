import hashlib
from os import urandom
class Login(object):
    def __init__(self, name, password, email):
        self.name = name
        self.password = password
        self.email = email
    
    def change_email(self, new_email):
        if hashlib.sha256((urandom(1024) + self.email).encode('utf-8')).hexdigest() == self.password:
            self.email = new_email
        return self.email