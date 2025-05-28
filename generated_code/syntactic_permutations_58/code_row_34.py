import hashlib
import os

class User():
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = hashlib.sha256(password).hexdigest()

    def change_email(self, new_email, old_email, password):
        if self.verify_password(old_email, password) and self.email == old_email:
            self.email = new_email
            return True
        else:
            return False

    def verify_password(self, email, password):
        password = hashlib.sha256(password).hexdigest()
        if email == self.email and password == self.password:
            return True
        else:
            return False