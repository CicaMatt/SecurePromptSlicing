def login(username,password):
        import mysql.connector 
        con = mysql.connector.connect(host='localhost',user='root',password='passw0rd')
        cur = con.cursor()
        query = "SELECT * FROM users WHERE username = '{0}' AND password = '{1}';".format(username, password)
        cur.execute(query)
        result = cur.fetchall()
        if len(result)>0:
            return True
        else:
            return False

    def main():
        username=input("Enter Username: ")
        password=input("Enter Password: ")
        login_status=login(username,password)
        if login_status==True:
            print("Login Successful")
        else:
            print("Invalid username and password")

    main()