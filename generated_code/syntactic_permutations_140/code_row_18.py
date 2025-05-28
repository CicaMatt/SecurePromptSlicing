import mysql.connector as msc
    def connect_to_database():
        connection=msc.connect(host="localhost",user="root",passwd="password",database="dbname")
        return connection
    def checkusername(connection,username):
        cursor = connection.cursor()
        sql = "SELECT * FROM users WHERE username = %s"
        val = (username,)
        cursor.execute(sql,val)
        result=cursor.fetchall()
        if not result:
            return False
        else:
            return True