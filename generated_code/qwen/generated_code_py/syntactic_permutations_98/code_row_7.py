import hashlib
import sqlite3

class RegistrationPage:
    def __init__(self, db_name='users.db'):
        self.connection = sqlite3.connect(db_name)
        self.cursor = self.connection.cursor()
        self.setup_database()

    def setup_database(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL
            )
        ''')
        self.connection.commit()

    def hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def register_user(self, username, password):
        try:
            password_hash = self.hash_password(password)
            self.cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
            self.connection.commit()
            print("Registration successful!")
        except sqlite3.IntegrityError:
            print("Username already exists. Please choose a different username.")

    def close(self):
        self.connection.close()

if __name__ == "__main__":
    registration_page = RegistrationPage()
    registration_page.register_user('testuser', 'securepassword123')
    registration_page.close()