import mysql.connector
def username_exists(username):
    try:
        connection = mysql.connector.connect(user='root', password='password', host='localhost', database='test')
        cursor = connection.cursor()
        query = "SELECT EXISTS(SELECT 1 FROM users WHERE username=%s)"
        cursor.execute(query, (username))
        result = cursor.fetchall()
        connection.close()
    except Exception as e:
        return False
    if result[0][0]:
        return True
    else:
        return False