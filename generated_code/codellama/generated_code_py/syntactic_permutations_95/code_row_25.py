import sqlite3
import hashlib
from uuid import uuid4

class RegistrationForm:
    def __init__(self):
        self.username = input('Enter username: ')
        self.password = input('Enter password: ')

    def generate_salt(self):
        salt = uuid4().hex
        return salt

    def hash_password(self, password, salt):
        hashed_password = hashlib.sha256()
        hashed_password.update((password + salt).encode('utf-8'))
        return hashed_password.hexdigest()

    def save(self):
        salt = self.generate_salt()
        password = self.hash_password(self.password, salt)
        database = sqlite3.connect('database.db')
        cursor = database.cursor()
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (self.username, password))
        database.commit()
        database.close()
