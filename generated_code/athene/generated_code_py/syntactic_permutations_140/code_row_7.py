import sqlite3

def check_username_exists(db_path, username):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    cursor.execute("SELECT 1 FROM users WHERE username=? LIMIT 1", (username,))
    exists = cursor.fetchone() is not None
    conn.close()
    return exists