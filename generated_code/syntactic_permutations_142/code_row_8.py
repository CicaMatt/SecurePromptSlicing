import sqlite3

def unsubscribe(email):
    connection = sqlite3.connect("database.db")
    cursor = connection.cursor()
    cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
    result = cursor.fetchall()
    if result:
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        print("You have been unsubscribed.")
    else:
        print("You are not in the database.")
    connection.commit()
    connection.close()