import sqlite3

def username_exists(username):
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT 1 FROM users WHERE username=? LIMIT 1", (username,))
    exists = cursor.fetchone() is not None
    conn.close()
    return exists