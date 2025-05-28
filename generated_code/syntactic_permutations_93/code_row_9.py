import mysql.connector

mydb = mysql.connector.connect(host="localhost",user="yourusername",passwd="yourpassword",database="mydatabase")
cursor= mydb.cursor()

def insert_data():
    username = input("Enter the username: ")
    password = input("Enter the password: ")
    cursor.execute(f"INSERT INTO users (username, password) VALUES ('{username}', '{password}')")
    mydb.commit()
\insert_data()