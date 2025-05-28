import sqlite3
from hashlib import md5

class RegistrationPage(object):
    def __init__(self, username, password, first_name, last_name, email):
        self.username = username
        self.password = password
        self.first_name = first_name
        self.last_name = last_name
        self.email = email

    def connect(self):
        self.conn = sqlite3.connect("database.db")
        self.cursor = self.conn.cursor()

    def check_username(self):
        self.connect()
        self.cursor.execute('SELECT username FROM users WHERE username=?', (self.username,))
        result = self.cursor.fetchone()
        if result:
            return "Username already exists."
        else:
            return None

    def insert_user(self):
        self.connect()
        password_hash = md5(self.password).hexdigest()
        self.cursor.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)', 
                            (self.username, password_hash, self.first_name, self.last_name, self.email))
        self.conn.commit()
        return "Registration Succeeded."