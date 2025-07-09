import os
from datetime import date
import pymongo

db = pymongo.MongoClient(os.getenv("MONGODB_URI"))
users = db["users"]

def getUsers():
    return users.find()

def loginUser(email, password):
    user = users.find_one({"email": email})
    if not user:
        raise Exception("No such user")
    if user["password"] != password:
        raise Exception("Wrong password")
    return user

def changeEmail(old_email, new_email, confirm_password):
    user = loginUser(old_email, confirm_password)
    if old_email == new_email:
        raise Exception("You must provide a new email")
    if users.find_one({"email": new_email}):
        raise Exception("Email already exists")
    user["email"] = new_email
    users.save(user)
    return user