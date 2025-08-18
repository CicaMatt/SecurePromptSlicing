import sqlite3

def is_moderator(db_path, username):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    cursor.execute("SELECT is_moderator FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()
    return bool(result[0]) if result else False