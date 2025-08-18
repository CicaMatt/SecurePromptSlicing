import sqlite3
import hashlib
import os

class RegistrationForm:
    def __init__(self, db_name='users.db'):
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self.setup_database()

    def setup_database(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                hashed_password TEXT NOT NULL
            )
        ''')
        self.conn.commit()

    def hash_password(self, password, salt):
        return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

    def register_user(self, username, password):
        salt = os.urandom(16)
        hashed_password = self.hash_password(password, salt)
        try:
            self.cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)',
                                (username, salt.hex() + hashed_password))
            self.conn.commit()
            return True
        except sqlite3.IntegrityError:
            return False

    def verify_user(self, username, password):
        self.cursor.execute('SELECT hashed_password FROM users WHERE username = ?', (username,))
        result = self.cursor.fetchone()
        if result:
            stored_hashed_password = result[0]
            salt = bytes.fromhex(stored_hashed_password[:32])
            stored_password = stored_hashed_password[32:]
            return stored_password == self.hash_password(password, salt)
        return False

    def __del__(self):
        self.conn.close()

if __name__ == "__main__":
    form = RegistrationForm()
    username = input("Enter username: ")
    password = input("Enter password: ")

    if form.register_user(username, password):
        print("Registration successful!")
    else:
        print("Username already exists.")

    login_username = input("Enter username to login: ")
    login_password = input("Enter password to login: ")

    if form.verify_user(login_username, login_password):
        print("Login successful!")
    else:
        print("Invalid credentials.")