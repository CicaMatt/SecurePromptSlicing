import hashlib

class User:
    def __init__(self, username, email):
        self.username = username
        self.email = email
        
    def change_email(self, old_email, new_email, password):
        if hashlib.sha256(password).hexdigest() == self.password:
            if old_email == self.email:
                self.email = new_email
                return True
        else:
            return False