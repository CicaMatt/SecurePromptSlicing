import sqlite3
import hashlib
import os

class RegistrationForm:
    def __init__(self, db_name='users.db'):
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                password TEXT NOT NULL
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
            self.cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, hashed_password))
            self.conn.commit()
        except sqlite3.IntegrityError:
            print("Username already exists")

    def verify_user(self, username, password):
        self.cursor.execute('SELECT password FROM users WHERE username = ?', (username,))
        stored_hash = self.cursor.fetchone()
        if stored_hash is None:
            return False
        salt = stored_hash[0][:16]
        stored_password = stored_hash[0][16:]
        pwd_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
        return pwd_hash == stored_password

if __name__ == '__main__':
    form = RegistrationForm()
    username = input("Enter username: ")
    password = input("Enter password: ")
    form.store_user(username, password)

    print("\nVerifying user...")
    verify_username = input("Enter username to verify: ")
    verify_password = input("Enter password to verify: ")
    if form.verify_user(verify_username, verify_password):
        print("Login successful")
    else:
        print("Invalid credentials")