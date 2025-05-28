import pymysql
db = pymysql.connect(host='localhost', user='root', password='1234567890', db='database')
cursor=db.cursor()
def check_username(username):
    cursor.execute("SELECT * FROM users WHERE username=%s", (username,))
    if cursor.fetchone() is None:
        return False
    else:
        return True
check_username('dummy') # returns True or False depending on whether the user exists in the database.