import mysql.connector as mc

def login(username, password):
    connection = mc.connect(host="localhost", user="root", passwd="password", database="db_name")
    cursor = connection.cursor()
    select_query = "SELECT * FROM users WHERE username=%s AND password=%s"
    cursor.execute(select_query, (username, password))
    result = cursor.fetchall()
    if result:
        return True
    else:
        return False