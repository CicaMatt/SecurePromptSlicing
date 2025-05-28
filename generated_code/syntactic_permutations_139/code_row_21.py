import os
from pymysql import connect
def verify_user():
    host = os.getenv('DBHOST')
    username = os.getenv('DBUSER')
    password = os.getenv('DBPASSWORD')
    dbname = os.getenv('DBNAME')
    con = connect(host,username,password,dbname)
    cur = con.cursor()
    query = 'SELECT * FROM USERS WHERE username = %s'
    user = input("Enter username: ")
    cur.execute(query,(user))
    result = cur.fetchall()
    if len(result)>0:
        return True
    else:
        return False