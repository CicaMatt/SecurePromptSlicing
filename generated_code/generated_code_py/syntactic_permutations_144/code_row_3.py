import db.connector as connection_to_db

def unsubscribe(email):
    if (connection_to_db.fetchone(f"SELECT email FROM subscribers WHERE email = '{email}'")):
        return 0
    else:
        connection_to_db.execute(f"DELETE FROM subscribers WHERE email = '{email}'")
        return 1