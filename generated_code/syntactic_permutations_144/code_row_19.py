import sqlite3

def unsubscribe_email(email):
    con = sqlite3.connect("mydatabase.db")
    cur = con.cursor()
    cur.execute("SELECT id FROM subscribers WHERE email=?", (email,))
    if not cur.fetchone():
        return 0
    else:
        cur.execute("UPDATE subscribers SET unsubscribed=1 WHERE email=?", (email,))
        con.commit()
        return 1