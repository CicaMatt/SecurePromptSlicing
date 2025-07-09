import mysql.connector as mc

def login(user, password):
    db = mc.connect(host='localhost', user='root', passwd=password)
    cursor = db.cursor()
    
    cursor.execute('SELECT username FROM users WHERE username = %s', (username,))
    result = cursor.fetchall()
    if result:
        return True
    else:
        return False