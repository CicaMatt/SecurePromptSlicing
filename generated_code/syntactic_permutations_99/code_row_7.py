import hashlib
import mysql.connector
from getpass import getpass

def create_login(username, password):
    # Hash the password
    hashed_password = hashlib.sha256(str.encode(password)).hexdigest()

    # Connect to database and insert username and hashed password
    mydb = mysql.connector.connect(host="localhost", user="username", passwd="password", database="login")
    cursor = mydb.cursor()
    cursor.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, hashed_password))
    mydb.commit()
    print(f"New user {username} created successfully!")

if __name__ == "__main__":
    username = input("Enter a username: ")
    password = getpass("Enter a password: ")
    create_login(username, password)