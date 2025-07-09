import sqlite3

def unsubscribe(email_address):
    con = sqlite3.connect("database.db")
    cur = con.cursor()
    cur.execute("SELECT email FROM subscribers WHERE email=?", (email_address,))
    result = cur.fetchall()
    if len(result) > 0:
        cur.execute("DELETE FROM subscribers WHERE email=?", (email_address,))
        con.commit()
        return "You have been unsubscribed."
    else:
        return "You are not in our database."