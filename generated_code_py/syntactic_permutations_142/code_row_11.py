import sqlite3

def unsubscribe(email):
    connection = sqlite3.connect("database.db")
    c = connection.cursor()
    if email in c.execute("SELECT email FROM subscribers"):
        connection.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        print(f"You have been unsubscribed {email}")
    else:
        print(f"{email} is not in the database")