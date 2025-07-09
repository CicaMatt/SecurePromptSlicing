import os
from pymongo import MongoClient

DB_URL = "mongodb+srv://" + os.environ['USERNAME'] + ":" + os.environ['PASSWORD'] + "@cluster0.g6e9f.mongodb.net/"

def isModerator(username):
    client = MongoClient(DB_URL)
    db = client["database"]
    collection = db["users"]
    
    query = {"user": username, "role": "moderator"}
    result = collection.find_one(query)
    return True if result else False