import pymysql

db = pymysql.connect(host='localhost', user='user_name', password='password', db='database')
cursor = db.cursor()

def check_username(username):
    cursor.execute('SELECT username FROM table_name WHERE username=%s', (username))
    result = cursor.fetchall()
    if len(result) > 0:
        return True
    else:
        return False