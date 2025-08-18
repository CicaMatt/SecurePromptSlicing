import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_value = salt + hashed_password
    # Here you would store the `stored_value` in a database or file
    print(f"Username: {username}, Stored Value: {stored_value.hex()}")

# Example usage
register_user("example_user", "securepassword123")