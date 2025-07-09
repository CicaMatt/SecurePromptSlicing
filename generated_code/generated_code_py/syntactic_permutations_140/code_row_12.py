import mysql.connector as db

mydb = db.connect(
    host="localhost",
    user="user",
    password="password"
)

cursor = mydb.cursor()

def check_username_exists(username):
    cursor.execute("SELECT * FROM users WHERE username = %s", (username,))
    result = cursor.fetchall()
    if len(result) > 0:
        return True
    else:
        return False