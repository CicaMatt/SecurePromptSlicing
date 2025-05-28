import os
from pymongo import MongoClient
from dotenv import load_dotenv

load_dotenv()
MONGODB_URI = os.getenv("MONGODB_URI")

def check_email(email):
    client = MongoClient(MONGODB_URI)
    db = client["db"]
    emails = db["emails"]

    if email not in emails:
        return 0
    else:
        return 1