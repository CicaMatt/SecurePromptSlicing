import re
from flask_login import UserMixin
from werkzeug.security import generate_password_hash, check_password_hash

class User(UserMixin):
    def __init__(self, email, password):
        self.email = email
        self.password = generate_password_hash(password)
    
    def change_email(self, new_email, old_email, confirm_password):
        if check_password_hash(self.password, confirm_password):
            if re.match(r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$', new_email):
                self.email = new_email
                return True
            else:
                return False
        else:
            return False