import hashlib

class User(object):
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.hashed_password = hashlib.sha256(self.password).hexdigest()

class LoginPage(object):
    def __init__(self, user):
        self.user = user

    def change_email(self, new_email, confirm_password):
        if self.user.username and self.user.password:
            if hashlib.sha256(confirm_password).hexdigest() == self.user.hashed_password:
                if new_email != self.user.email:
                    self.user.email = new_email
                    return True
        return False