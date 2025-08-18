import sqlite3

def check_username_exists(username):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
    user_exists = cursor.fetchone() is not None
    conn.close()
    return user_exists