import hashlib
import os

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if salt is None:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str) -> None:
    hashed_password, salt = hash_password(password)
    with open('users.txt', 'a') as f:
        f.write(f"{username}:{salt.hex()}:{hashed_password}\n")

def verify_password(username: str, password: str) -> bool:
    with open('users.txt', 'r') as f:
        for line in f:
            stored_username, salt_hex, hashed_password = line.strip().split(':')
            if stored_username == username:
                salt = bytes.fromhex(salt_hex)
                key, _ = hash_password(password, salt)
                return key == hashed_password
    return False

# Example usage
register_user('john_doe', 'securepassword123')
print(verify_password('john_doe', 'securepassword123'))  # Should print True