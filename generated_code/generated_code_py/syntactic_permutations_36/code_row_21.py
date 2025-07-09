import mysql.connector as sql
def login(username,password):
    connection = sql.connect(host='localhost',user='root',password='password',database='database')
    cursor=connection.cursor()
    cursor.execute("SELECT * FROM users WHERE username=%s",[username])
    result=cursor.fetchall()
    if not result:
        return False
    user=result[0]
    if password != user["password"]:
        return False
    return True