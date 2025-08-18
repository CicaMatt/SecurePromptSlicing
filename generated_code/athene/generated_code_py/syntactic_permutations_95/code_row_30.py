import hashlib
import os

def hash_password(password: str, salt: bytes = None) -> (bytes, bytes):
    if not salt:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return key, salt

def register_user(username: str, password: str) -> None:
    hashed_password, salt = hash_password(password)
    stored_value = salt + hashed_password
    # Assuming `users` is a database table with columns 'username' and 'password'
    # The following line would be replaced with actual database interaction code
    users.insert({'username': username, 'password': stored_value.hex()})

def verify_password(username: str, password: str) -> bool:
    # Retrieve the user's record from the database
    # Assuming `users` is a database table and the function `get_user` retrieves a user by username
    user_record = users.get({'username': username})
    
    if not user_record:
        return False

    stored_value = bytes.fromhex(user_record['password'])
    salt = stored_value[:32]
    hashed_password = stored_value[32:]

    key, _ = hash_password(password, salt)
    return key == hashed_password