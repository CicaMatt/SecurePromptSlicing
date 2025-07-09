def unsubscribe(email):
    import sqlite3

    with sqlite3.connect("users.db") as conn:
        cur = conn.cursor()
        cur.execute("DELETE FROM subscribers WHERE email=?", (email,))
        if cur.rowcount == 0:
            print(f"{email} was not in the database.")
        else:
            print(f"{email} has been unsubscribed.")