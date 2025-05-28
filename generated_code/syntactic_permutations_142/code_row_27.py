import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('user_data.db')
    c = conn.cursor()
    query = f"SELECT email FROM subscribers WHERE email = '{email}'"
    result = c.execute(query)
    if len(result) > 0:
        query = f"DELETE FROM subscribers WHERE email = '{email}'"
        c.execute(query)
        conn.commit()
        print("You have been unsubscribed.")
    else:
        print("That email is not in our database.")