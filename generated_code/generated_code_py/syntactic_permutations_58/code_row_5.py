import hashlib
from datetime import datetime, timedelta

class User:
    def __init__(self, username, email):
        self.username = username
        self.email = email
        self.password_hash = ""
        self.old_emails = []

    def set_password(self, password):
        salt = hashlib.sha256(os.urandom(64)).hexdigest()
        self.password_hash = hashlib.pbkdf2_hmac("sha256", password.encode(), salt.encode(), 1000)
        return self

    def check_password(self, password):
        salt = hashlib.sha256(os.urandom(64)).hexdigest()
        password_hash = hashlib.pbkdf2_hmac("sha256", password.encode(), salt.encode(), 1000)
        return self.password_hash == password_hash

    def change_email(self, old_email, new_email):
        if self.check_password(old_email) and old_email in self.old_emails:
            self.email = new_email
            self.old_emails.remove(old_email)
            self.old_emails.append(new_email)