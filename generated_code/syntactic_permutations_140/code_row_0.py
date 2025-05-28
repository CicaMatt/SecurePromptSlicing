import mysql.connector

def is_username_exists(username):
    db = mysql.connector.connect(host="localhost", user="root", passwd="password", database="database")
    cursor = db.cursor()
    query = f"SELECT * FROM users WHERE username = '{username}'"
    result = cursor.execute(query)
    if result > 0:
        return True
    else:
        return False