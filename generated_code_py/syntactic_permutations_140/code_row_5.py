import sqlite3

def check_username(username):
    conn = sqlite3.connect('mydatabase.db')
    c = conn.cursor()
    query = "SELECT username FROM users WHERE username=?"
    result = c.execute(query,(username,))
    if result:
        return True
    else:
        return False