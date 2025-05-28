import sqlite3

def unsubscribe(email):
    con = sqlite3.connect('database.db')
    cur = con.cursor()
    cur.execute("SELECT * FROM users WHERE email=?", (email,))
    row = cur.fetchone()
    if row:
        cur.execute("DELETE FROM users WHERE email=?", (email,))
        con.commit()
        return "You have been unsubscribed"
    else:
        return "You are not subscribed"