import hashlib
import sqlite3

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
    passwd = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), salt, 100000)
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, salt + passwd))
    conn.commit()
    conn.close()