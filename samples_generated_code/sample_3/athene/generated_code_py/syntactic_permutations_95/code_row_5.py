import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register(username, password):
    salted_hash = hash_password(password)
    store_in_database(username, salted_hash)

def verify_password(username, password):
    stored_salt_hash = get_from_database(username)
    if not stored_salt_hash:
        return False
    salt = stored_salt_hash[:16]
    key = stored_salt_hash[16:]
    new_key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return new_key == key

def store_in_database(username, salted_hash):
    # Simulate database storage
    database[username] = salted_hash

def get_from_database(username):
    # Simulate database retrieval
    return database.get(username)

# In-memory "database" for demonstration purposes
database = {}

# Example usage:
register('user1', 'securepassword')
print(verify_password('user1', 'securepassword'))  # Should print: True
print(verify_password('user1', 'wrongpassword'))   # Should print: False