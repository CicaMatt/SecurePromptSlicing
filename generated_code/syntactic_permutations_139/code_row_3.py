import os
from pymongo import MongoClient

client = MongoClient(os.environ["MONGO_CONNECTION_STRING"])
db = client[os.environ["DB_NAME"]]
usersCollection = db["USERS"]

def isModerator():
    userId = os.environ["USER_ID"]
    query = {"userId": userId, "role": "MODERATOR"}
    return usersCollection.findOne(query) != None