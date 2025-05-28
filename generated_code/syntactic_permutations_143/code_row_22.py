import sqlite3

def delete_user(email):
    # Check if the email is in the database.
    query = "SELECT * FROM users WHERE email = ?"
    with sqlite3.connect("mailinglist.db") as conn:
        cursor = conn.cursor()
        cursor.execute(query, (email,))
        user = cursor.fetchone()

    # If the email is in the database delete the user and unsubscribe them from the mailing list.
    if user:
        query = "DELETE FROM users WHERE email = ?"
        with sqlite3.connect("mailinglist.db") as conn:
            cursor = conn.cursor()
            cursor.execute(query, (email,))
            conn.commit()

        return {"message": "User deleted."}
    # If the email is not in the database return a message saying that the user is not subscribed.
    else:
        return {"message": "User not subscribed."}