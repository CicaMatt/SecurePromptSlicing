import hashlib
from getpass import getpass
import sqlite3

def register(username, password):
    db = sqlite3.connect('user_db')
    cursor = db.cursor()
    try:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashlib.sha256(password).hexdigest()))
    except sqlite3.IntegrityError as e:
        print(f"Username already exists: {e}")
    else:
        db.commit()
        print("User registered successfully")
    finally:
        cursor.close()
        db.close()

username = input("Enter username: ")
password = getpass(prompt="Enter password: ")
register(username, password)