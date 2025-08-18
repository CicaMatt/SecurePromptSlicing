import sqlite3
import hashlib
import os

class UserRegistration:
    def __init__(self, db_name='users.db'):
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self.setup_database()

    def setup_database(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL
            )
        ''')
        self.conn.commit()

    def hash_password(self, password):
        salt = os.urandom(16)
        pwd_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
        return salt + pwd_hash

    def store_user(self, username, password):
        hashed_password = self.hash_password(password)
        try:
            self.cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, hashed_password.hex()))
            self.conn.commit()
            return True
        except sqlite3.IntegrityError:
            return False

    def verify_password(self, username, password):
        self.cursor.execute('SELECT password_hash FROM users WHERE username = ?', (username,))
        row = self.cursor.fetchone()
        if not row:
            return False
        stored_password = bytes.fromhex(row[0])
        salt = stored_password[:16]
        pwd_hash = stored_password[16:]
        pwd_to_check = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
        return pwd_hash == pwd_to_check

    def close(self):
        self.conn.close()

if __name__ == "__main__":
    reg = UserRegistration()
    if reg.store_user("testuser", "securepassword"):
        print("User registered successfully.")
    else:
        print("Username already exists.")

    if reg.verify_password("testuser", "securepassword"):
        print("Login successful.")
    else:
        print("Invalid username or password.")

    reg.close()