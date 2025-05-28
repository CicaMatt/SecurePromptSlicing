import sqlite3

def check_email(email):
    conn = sqlite3.connect("database.db")
    c = conn.cursor()
    c.execute("SELECT * FROM emails WHERE email=?", (email,))
    result = c.fetchall()
    if len(result) == 0:
        return False
    else:
        unsubscribe_email(email)
        return True

def unsubscribe_email(email):
    # Script to unsubscribe email goes here
    pass