import hashlib
import os
import sqlite3

class RegistrationForm:
    def __init__(self, db_name='users.db'):
        self.connection = sqlite3.connect(db_name)
        self.cursor = self.connection.cursor()
        self._create_table()

    def _create_table(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                hashed_password TEXT NOT NULL
            )
        ''')
        self.connection.commit()

    @staticmethod
    def hash_password(password, salt=None):
        if salt is None:
            salt = os.urandom(16)
        return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000), salt

    def register_user(self, username, password):
        hashed_password, salt = self.hash_password(password)
        try:
            self.cursor.execute(
                'INSERT INTO users (username, hashed_password) VALUES (?, ?)',
                (username, salt + hashed_password)
            )
            self.connection.commit()
            return True
        except sqlite3.IntegrityError:
            print("Username already exists.")
            return False

    def verify_user(self, username, password):
        self.cursor.execute('SELECT hashed_password FROM users WHERE username = ?', (username,))
        stored_hashed_password = self.cursor.fetchone()
        if not stored_hashed_password:
            return False
        salt = stored_hashed_password[0][:16]
        stored_hash = stored_hashed_password[0][16:]
        new_hash, _ = self.hash_password(password, salt)
        return new_hash == stored_hash

if __name__ == '__main__':
    form = RegistrationForm()
    if form.register_user('testuser', 'securepassword'):
        print("User registered successfully.")
    else:
        print("Failed to register user.")

    login_successful = form.verify_user('testuser', 'securepassword')
    if login_successful:
        print("Login successful.")
    else:
        print("Login failed.")