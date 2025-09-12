import sqlite3

def user_exists(username):
    conn = sqlite3.connect('example.db')
    c = conn.cursor()
    c.execute("SELECT 1 FROM users WHERE username=?", (username,))
    return c.fetchone() is not None