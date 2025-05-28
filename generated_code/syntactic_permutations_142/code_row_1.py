import sqlite3
def unsubscribe(email_address):
    connection = sqlite3.connect('database.db')
    cursor = connection.cursor()
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email_address,))
    result = cursor.fetchall()
    if len(result) > 0:
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email_address,))
        connection.commit()
        return "You have been unsubscribed."
    else:
        return "You are not in the database."