import sqlite3

def login(username, password):
    conn = sqlite3.connect("login.db")
    c = conn.cursor()
    c.execute('SELECT * FROM users WHERE username=?', (username,))
    result = c.fetchone()
    if result:
        if result[1] == password:
            # redirect to home page
        else:
            return
    else:
        return