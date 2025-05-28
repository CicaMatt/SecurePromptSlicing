import hashlib
from pymongo import MongoClient

username = input("Enter your username: ")
password = input("Enter your password: ")
salt = b"\xb9\xa2|\x0eP\xd1\x8c\xc3'\xaa\xfaX\x86\x92\xfd\x14"
hashed_password = hashlib.pbkdf2_hmac("sha512", password.encode(), salt, 100000)

client = MongoClient("mongodb://localhost:27017/")
db = client["login"]
collection = db["user_credentials"]

try:
    collection.insert_one({"username": username, "hashed_password": hashed_password})
except Exception as e:
    print(e)


### Explanation: 
The code first imports the necessary libraries: `hashlib` and `pymongo`. It then prompts the user to enter a username and password, which are assigned to variables. The salt is defined next, and the hashed password is calculated using the `pbkdf2_hmac()` function of the `hashlib` library. Finally, the code connects to a MongoDB server at `localhost:27017`, selects the "login" database and the "user_credentials" collection. It then tries to insert a new document into the collection with the username and hashed password as key-value pairs.