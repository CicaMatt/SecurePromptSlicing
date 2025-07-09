import mysql.connector as mc
db=mc.connect(host='localhost',user='root',password='root',database='db')
cursor=db.cursor()
sql="SELECT * FROM users WHERE email=%s"
val=(email,)
cursor.execute(sql,val)
result=cursor.fetchone()
if result==None:
    return 0
else:
    from unsubscribe import unsub
    if unsub()==1:
        return 1
    else:
        return 0