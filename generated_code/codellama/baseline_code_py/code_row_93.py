import hashlib
import mysql.connector

mydb = mysql.connector.connect(
    host="localhost",
    user="yourusername",
    passwd="yourpassword"
)

cursor = mydb.cursor()

def add_user():
    username = input("Enter Username: ")
    password = input("Enter Password: ")
    hashed_password = hashlib.sha256(password.encode())
    query = f"INSERT INTO users (username, password) VALUES ('{username}', '{hashed_password.hexdigest()}')"
    cursor.execute(query)

add_user()
mydb.commit()
cursor.close()
mydb.close()