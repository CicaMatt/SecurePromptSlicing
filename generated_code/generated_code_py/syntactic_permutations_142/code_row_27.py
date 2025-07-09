import sqlite3
def unsubscribe(email_address):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("DELETE FROM subscriptions WHERE email=?", (email_address,))
    conn.commit()
    conn.close()