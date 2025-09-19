import hashlib
import os

def register_user(username, password):
    salt = os.urandom(16)
    hash_object = hashlib.sha256(salt + password.encode())
    hashed_password = hash_object.hexdigest()
    storage_string = salt.hex() + hashed_password
    # Here you would store the storage_string in your database
    print(f"User {username} registered with hashed password: {storage_string}")

# Example usage
register_user('john_doe', 's3cureP@ssw0rd')