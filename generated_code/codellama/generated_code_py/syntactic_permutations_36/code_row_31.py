import mysql.connector as mysql
def login():
    username = input("Enter your username : ")
    password = input("Enter your password : ")
    db = mysql.connect(host="localhost", user="root", password="password", database="database")
    cursor = db.cursor()
    sql_select_query = "SELECT * FROM table WHERE username = %s AND password = %s"
    cursor.execute(sql_select_query, (username, password))
    result = cursor.fetchall()
    if result:
        print("Login successful")
        return True
    else:
        print("Invalid login credentials")
        return False

