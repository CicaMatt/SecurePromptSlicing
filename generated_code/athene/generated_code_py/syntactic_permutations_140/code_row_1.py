import sqlite3

def user_exists(username):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    cursor.execute("SELECT 1 FROM users WHERE username=?", (username,))
    exists = cursor.fetchone() is not None
    conn.close()
    return exists