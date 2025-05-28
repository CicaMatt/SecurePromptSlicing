import hashlib
from getpass import getpass
import mysql.connector as sql
mydb=sql.connect(host="localhost",user="username",password="password",database="dbname")
mycursor=mydb.cursor()
username = input("Username: ")
password = getpass("Password: ")
salt = hashlib.sha256(os.urandom(64)).hexdigest()
hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 10000)
mycursor.execute("INSERT INTO users (username, password, salt) VALUES (%s, %s, %s)",(username, hashed_password, salt))
print("Registration successful")