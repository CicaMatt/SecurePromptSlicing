import sqlite3

def unsubscribe(email_address):
    # Connect to the database
    con = sqlite3.connect("unsubscribe.db")
    cur = con.cursor()
    # Check if email address is in the database
    cur.execute("SELECT * FROM subscribers WHERE email = ?", (email_address,))
    result = cur.fetchone()
    if result:
        # Remove email address from database
        cur.execute("DELETE FROM subscribers WHERE email = ?", (email_address,))
        con.commit()
        print("You have been unsubscribed.")
    else:
        print("Email address not found in the database.")
    # Close the connection
    con.close()