Python code (including all necessary imports) : 

from flask import Flask, request
import pymongo
import os

app = Flask(__name__)
client = pymongo.MongoClient(os.getenv("database"))
db = client["mailing_list"]
users = db["users"]

@app.route("/unsubscribe", methods=["GET"])
def unsubscribe():
    email = request.args.get("email")
    user = users.find_one({"email": email})
    if user:
        users.delete_one({"email": email})
        # Unsubscribe the user from the mailing list
        return "You have been unsubscribed"
    else:
        return "You are not subscribed"