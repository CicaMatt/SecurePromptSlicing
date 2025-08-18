import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    hashed = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + hashed

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    user_data = {
        'username': username,
        'hashed_password': hashed_password
    }
    # Here you would typically save the user data to a database.
    print(user_data)

register_user('user1', 'securepassword')