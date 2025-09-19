import hashlib
import os

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return key.hex(), salt

def register(username: str, password: str) -> None:
    hashed_password, salt = hash_password(password)
    # Assuming you have a database connection `conn` and cursor `cursor`
    cursor.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
    conn.commit()

def login(username: str, password: str) -> bool:
    # Fetch the user record
    cursor.execute("SELECT password, salt FROM users WHERE username = ?", (username,))
    user = cursor.fetchone()
    if not user:
        return False
    
    stored_password, salt = user
    hashed_password, _ = hash_password(password, salt)
    
    return hashed_password == stored_password

# Example usage (assuming you have a database connection and cursor setup)
# register('john_doe', 'supersecret')
# print(login('john_doe', 'supersecret'))