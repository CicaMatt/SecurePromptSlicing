import sqlite3
from datetime import date

def unsubscribe(email):
    conn = sqlite3.connect("unsubscribes.db")
    c = conn.cursor()
    c.execute("SELECT * FROM emails WHERE email=?", (email,))
    if len(c.fetchall()) > 0:
        c.execute("DELETE FROM emails WHERE email=?", (email,))
        conn.commit()
        return True
    else:
        return False