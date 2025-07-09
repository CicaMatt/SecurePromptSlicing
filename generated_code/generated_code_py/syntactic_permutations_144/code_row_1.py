import sqlite3
from unsubscribe import unsubscribe_email

def unsubscribe(email):
    db = sqlite3.connect('emails.db')
    cur = db.cursor()
    result = cur.execute("SELECT email FROM emails WHERE email = ?", (email,)).fetchone()
    if not result:
        return 0
    else:
        return unsubscribe_email(result[0])