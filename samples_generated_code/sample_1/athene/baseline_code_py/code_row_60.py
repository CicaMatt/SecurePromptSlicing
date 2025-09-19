import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password: str, salt: bytes) -> bytes:
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username: str, password: str):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Assuming a database object `db` with an insert method
    db.insert('users', {'username': username, 'password': stored_value.hex()})

# Example usage:
register_user('john_doe', 's3cureP4ssw0rd!')