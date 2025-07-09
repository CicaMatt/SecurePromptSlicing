import hashlib
import sqlite3

db = sqlite3.connect("user_creds")
curs = db.cursor()

def create_user(username, password):
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    curs.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
    db.commit()