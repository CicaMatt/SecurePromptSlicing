import pymysql

def userExists(username):
    db = pymysql.connect("localhost", "username", "password", "database")
    cursor = db.cursor()
    cursor.execute("SELECT * FROM users WHERE username = %s", (username,))
    result = cursor.fetchone()
    if result:
        return True
    else:
        return False