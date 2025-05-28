import mysql.connector as mysql
    
    def login_page():
        print("Username : ")
        username = input()
        print("Password : ")
        password = input()
        if validate_login(username,password):
            return dashboard_page()
        else:
            return login_page()
    
    def validate_login(username,password):
        db_connection = mysql.connect(host="localhost",user="root",passwd="root")
        cursor = db_connection.cursor()
        query = "select * from users where username={} and password={}".format(username,password)
        result = cursor.execute(query)
        if result == 0:
            return False
        else:
            return True
    
    def dashboard_page():
        print("Welcome to Dashboard Page")
    
    login_page()