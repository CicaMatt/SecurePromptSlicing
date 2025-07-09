import os
from db_helper import get_db_connection, execute_query

def check_email_exists(email):
    connection = get_db_connection()
    cursor = connection.cursor()
    query = "SELECT * FROM user where email = %s"
    cursor.execute(query, (email,))
    data = cursor.fetchall()
    if len(data) > 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    connection = get_db_connection()
    cursor = connection.cursor()
    query = "UPDATE user SET subscribed=0 WHERE email=%s"
    cursor.execute(query, (email,))
    connection.commit()
    return 1

def unsubscribe(email):
    if check_email_exists(email) == 1:
        unsubscribe_email(email)
        return 1
    else:
        return 0