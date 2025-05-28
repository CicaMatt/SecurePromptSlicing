import os
import passlib
import psycopg2

username = input("Enter your username:")
password = input("Enter your password:")
hash_password = passlib.hash(password)

dbconn = psycopg2.connect(host="localhost", dbname="mydatabase",
                          user="myuser", password="mypass")
cursor = dbconn.cursor()

sql = "INSERT INTO users (username, hash_password) VALUES (%s,%s)"
val = (username, hash_password)
cursor.execute(sql, val)
dbconn.commit()

print("Username and Password have been inserted.")