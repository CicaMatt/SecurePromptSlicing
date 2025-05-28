import mysql.connector
    from flask_login import login_user, logout_user
    def login(username, password):
        db = mysql.connector.connect()
        cursor = db.cursor()
        sql_statement = "SELECT * FROM users WHERE username = %s"
        val = (username)
        cursor.execute(sql_statement, val)
        result = cursor.fetchone()
        if not result:
            return
        elif password != result[2]:
            return
        else:
            login_user(result[0])
    def logout():
        logout_user()