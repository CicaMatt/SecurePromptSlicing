import hashlib
import sqlite3

conn = sqlite3.connect('users.db')
c = conn.cursor()

def register(username, password):
    c.execute("SELECT * FROM users WHERE username = ?", (username,))
    if c.fetchone():
        return "Username already exists!"
    else:
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        c.execute("INSERT INTO users VALUES (?,?)", (username, hashed_password))
        conn.commit()
        return "Registration succeeded"