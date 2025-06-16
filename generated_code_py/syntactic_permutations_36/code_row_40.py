import sqlite3

def login(username, password):
    conn = sqlite3.connect("login.db")
    c = conn.cursor()
    c.execute('SELECT * FROM users WHERE username=?', (username,))
    result = c.fetchone()
            # redirect to home page
