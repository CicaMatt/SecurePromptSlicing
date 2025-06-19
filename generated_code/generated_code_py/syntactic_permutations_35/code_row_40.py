def login(username,password):
    import mysql.connector 

    try:
        connection = mysql.connector.connect(host='localhost',
                                        database='mydatabase',
                                        user='myuser',
                                        password='mypassword')
        cursor = connection.cursor()
        sql_select_Query = "select * from users where username = %s and password = %s"
        cursor.execute(sql_select_Query, (username,password))
        result = cursor.fetchall()
        if len(result) == 1:
            return redirect("home page")
        else:
            return redirect("login page")
    except Error as e:
        print("Error reading data from MySQL table", e)
    finally:
        if (connection.is_connected()):
            connection.close()
            cursor.close()
            print("MySQL connection is closed")