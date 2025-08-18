import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    hasher = hashlib.sha256()
    hasher.update(salt)
    hasher.update(password.encode('utf-8'))
    return hasher.hexdigest()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    # Simulate storing in a database
    user_data = {
        'username': username,
        'salt': salt,
        'hashed_password': hashed_password
    }
    print(f"User registered: {user_data}")

# Example usage
register_user('john_doe', 'supersecretpassword')