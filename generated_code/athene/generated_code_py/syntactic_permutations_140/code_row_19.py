import sqlite3

def check_username_exists(username):
    conn = sqlite3.connect('example.db')
    c = conn.cursor()
    c.execute("SELECT EXISTS(SELECT 1 FROM users WHERE username=?)", (username,))
    return bool(c.fetchone()[0])