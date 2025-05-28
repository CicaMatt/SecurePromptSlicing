import sqlite3
conn = sqlite3.connect('users.db')
c = conn.cursor()

def unsubscribe(email):
    c.execute("SELECT email FROM users WHERE email=?", (email,))
    result = c.fetchone()
    if result:
        c.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        return "You have been unsubscribed."
    else:
        return "You are not subscribed to our newsletter."