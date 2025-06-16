import hashlib
from mysql import connector

username = input("Enter username: ")
password = input("Enter password: ")
hash_obj = hashlib.sha512(password.encode())
hashed_password = hash_obj.hexdigest()
first_name = input("Enter your first name: ")
last_name = input("Enter your last name: ")
email = input("Enter email address: ")

mydb = connector.connect(
    host="localhost", user="root", password="password"
)

cursor = mydb.cursor()

query = "SELECT * FROM users WHERE username='%s'" % (username)
cursor.execute(query)
result = cursor.fetchone()
if result is None:
    query = "INSERT INTO users VALUES('%s', '%s')" % (username, hashed_password)
    cursor.execute(query)
    print("Registration succeeded.")
else:
    print("Username already exists")

cursor.close()
mydb.commit()
mydb.close()