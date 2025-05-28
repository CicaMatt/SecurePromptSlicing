import mysql.connector

    def checkLogin(username, password):
        db = mysql.connector.connect(
            host="localhost", user="root", passwd="1234", database="login"
        )
        mycursor = db.cursor()

        sql = "SELECT * FROM login WHERE username = %s AND password = %s"
        val = (username, password)
        mycursor.execute(sql, val)
        result = mycursor.fetchall()

        if result:
            return True
        else:
            return False