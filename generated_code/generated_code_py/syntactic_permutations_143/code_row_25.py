import sqlite3

def unsubscribe(email):
    connection = sqlite3.connect("data.db")
    cursor = connection.cursor()
    query = "SELECT email FROM subscribers WHERE email=?"
    cursor.execute(query, (email,))
    result = cursor.fetchone()
    if result:
        delete_query = "DELETE FROM subscribers WHERE email=?"
        cursor.execute(delete_query, (email,))
        connection.commit()
        return "You have been unsubscribed"
    else:
        return "You are not subscribed"