import sqlite3

def check_username_exists(username):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    cursor.execute("SELECT 1 FROM users WHERE username=?", (username,))
    result = cursor.fetchone() is not None
    cursor.close()
    conn.close()
    return result