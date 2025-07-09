import mysql.connector

def db_connect():
    cnx = mysql.connector.connect(user='root', password='password', host='localhost', database='db')
    return cnx

def check_username(username):
    cnx = db_connect()
    cursor = cnx.cursor()
    query = "SELECT username FROM users WHERE username = %s"
    cursor.execute(query, (username,))
    result = cursor.fetchall()
    if result:
        return True
    else:
        return False