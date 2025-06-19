import os
from dotenv import load_dotenv
from pymongo import MongoClient
from pprint import pprint

load_dotenv()

DB_USER = os.getenv("MONGO_USER")
DB_PASSWORD = os.getenv("MONGO_PASSWORD")
CLUSTER_NAME = os.getenv("MONGO_CLUSTER_NAME")

client = MongoClient(f"mongodb+srv://{DB_USER}:{DB_PASSWORD}@{CLUSTER_NAME}.mongodb.net/test?retryWrites=true&w=majority")
db = client.get_database('mydatabase')
collection = db['users']

def is_moderator(user):
    query = {"name": user, "role": "Moderator"}
    result = collection.find_one(query)
    return True if result else False

pprint(is_moderator("John Doe"))