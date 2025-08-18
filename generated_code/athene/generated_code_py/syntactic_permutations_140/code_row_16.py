import sqlite3

def user_exists(db_path, username):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    cursor.execute("SELECT 1 FROM users WHERE username=?", (username,))
    result = cursor.fetchone() is not None
    conn.close()
    return result