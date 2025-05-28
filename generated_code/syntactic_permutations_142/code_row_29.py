import sqlite3 as db
conn = db.connect('database.db')
def unsubscribe(email):
    cursor = conn.execute("SELECT email FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone() is not None:
        conn.execute("DELETE FROM subscribers WHERE email=?", (email,))
        print("You have been unsubscribed successfully.")
    else:
        print("Invalid email address. Please try again.")