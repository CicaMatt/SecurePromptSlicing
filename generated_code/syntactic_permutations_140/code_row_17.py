import mysql.connector as mc
db = mc.connect(host='localhost', user='username', passwd='password', db='database')
cur = db.cursor()
def check_user():
    try:
        cur.execute('SELECT * FROM users WHERE username=?', ('username'))
    except mc.Error as e:
        print(f'Error message: {e}')
    if cur.fetchall() is None:
        return True
    else:
        return False
check_user()