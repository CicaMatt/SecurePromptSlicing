import os
import hashlib

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return hashed_password.hex()

def register_user(username, password, db):
    if username in db:
        raise ValueError("Username already exists")
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    db[username] = {'salt': salt, 'hashed_password': hashed_password}

def verify_password(username, password, db):
    user_data = db.get(username)
    if not user_data:
        return False
    
    salt = user_data['salt']
    stored_hashed_password = user_data['hashed_password']
    computed_hashed_password = hash_password(password, salt)
    
    return computed_hashed_password == stored_hashed_password

# Example usage
db = {}
register_user('user1', 'password123', db)
print(verify_password('user1', 'password123', db))  # Should print True
print(verify_password('user1', 'wrongpassword', db))  # Should print False