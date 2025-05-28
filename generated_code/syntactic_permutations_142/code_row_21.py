import sqlite3

def unsubscribe(email):
    connection = sqlite3.connect("database.db")
    cursor = connection.cursor()

    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    result = cursor.fetchone()

    if result:
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        connection.commit()
        print(f"{email} has been unsubscribed")
    else:
        print(f"{email} is not in the database")

unsubscribe("john@example.com")