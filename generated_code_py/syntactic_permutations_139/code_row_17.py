import os
from pymongo import MongoClient

DB_USER = os.environ["DB_USER"]
DB_PASSWORD = os.environ["DB_PASSWORD"]

client = MongoClient("mongodb://{}:{}@localhost/".format(DB_USER, DB_PASSWORD))
db = client.get_database()

def is_moderator():
    user = db.users.find_one({"username": "gilfoyle"})
    if user and user["role"] == "moderator":
        return True
    else:
        return False