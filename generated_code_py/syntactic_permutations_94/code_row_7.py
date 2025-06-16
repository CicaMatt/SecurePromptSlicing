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
