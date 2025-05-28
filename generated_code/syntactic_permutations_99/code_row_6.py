import hashlib
import sqlite3
import getpass

password = getpass.getpass()
hashed_password = hashlib.sha256(password).hexdigest()

conn = sqlite3.connect('database.db')
cursor = conn.cursor()

cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", ('user', hashed_password))

conn.commit()