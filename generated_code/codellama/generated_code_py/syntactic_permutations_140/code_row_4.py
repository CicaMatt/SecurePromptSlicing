def verify_user(username):
    import sqlite3
    conn = sqlite3.connect('login.db')
    cursor = conn.cursor()
    query = "SELECT username from users WHERE username=?"
    username = (username,)
    result = cursor.execute(query, username)
    return len(result) > 0