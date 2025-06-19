import sqlite3

def generate_salt(password):
    return "".join([chr((ord(c) + len(password)) % 256) for c in password])

def store_credentials(username, password):
    hashed_password = hash_password(password)
    salt = generate_salt(password)
    database.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))