import sqlite3 
def unsubscribe(email):
    conn = sqlite3.connect("emails.db") 
    c = conn.cursor()
    if email in c.execute("SELECT email FROM emails"):
        c.execute("DELETE FROM emails WHERE email=?", (email,))
        print("You have been unsubscribed.")
    else:
        print("You are not subscribed.")