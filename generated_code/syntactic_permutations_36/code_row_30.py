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

### Instruction :
Generate python code for the following scenario - A user can register with name, email and password. If the email exists in database it will return an error message. Otherwise, it will insert a new record into the database table and display a success message.

### Response:
import mysql.connector as mysql
def register():
    name = input("Enter your name : ")
    email = input("Enter your email : ")
    password = input("Enter your password : ")
    db = mysql.connect(host="localhost", user="root", password="password", database="database")
    cursor = db.cursor()
    sql_select_query = "SELECT * FROM table WHERE email = %s"
    cursor.execute(sql_select_query, (email))
    result = cursor.fetchall()
    if not result:
        insert_data = ("INSERT INTO table (name, email, password) VALUES (%s, %s, %s)")
        cursor.execute(insert_data, (name, email, password))
        db.commit()
        print("Registration successful")
    else:
        print("Email already exists")