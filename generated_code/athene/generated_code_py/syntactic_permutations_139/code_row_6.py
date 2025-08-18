import sqlite3

def is_moderator(user_id, db_path):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    cursor.execute("SELECT EXISTS(SELECT 1 FROM users WHERE id=? AND is_moderator=1)", (user_id,))
    result = cursor.fetchone()[0]
    conn.close()
    return bool(result)