import hashlib
import sqlite3

def register(username, password, first_name, last_name, email):
    # Hash the password for storage
    hashed_password = hashlib.sha256(password).hexdigest()
    
    # Connect to the database and insert the user information
    with sqlite3.connect("register.db") as db:
        cursor = db.cursor()
        cursor.execute("SELECT username FROM users WHERE username = ?", (username,))
        result = cursor.fetchone()
        if result is not None:
            return "Username already exists"
        else:
            cursor.execute(
                "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                (username, hashed_password, first_name, last_name, email)
            )
            return "Registration succeeded"