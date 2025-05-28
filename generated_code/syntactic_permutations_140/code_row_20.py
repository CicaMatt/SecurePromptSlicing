import mysql.connector as mc
db = mc.connect(host="localhost", user="root", password="password", db="mydatabase")
cursor = db.cursor()
def check_username_exists(username):
    query = "SELECT * FROM users WHERE username = %s"
    cursor.execute(query, (username,))
    result = cursor.fetchall()
    if result:
        return True
    else:
        return False