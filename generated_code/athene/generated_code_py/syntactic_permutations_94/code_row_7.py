import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register_user(username, password, db_connection):
    cursor = db_connection.cursor()
    hashed_password = hash_password(password)
    query = "INSERT INTO users (username, password) VALUES (%s, %s)"
    cursor.execute(query, (username, hashed_password))
    db_connection.commit()

# Example usage
import sqlite3

db_connection = sqlite3.connect('test.db')
register_user('john_doe', 'mysecurepassword123', db_connection)
db_connection.close()