from flask import Flask
app = Flask(__name__)

@app.route("/is_moderator")
def is_moderator():
    from pymongo import MongoClient
    client = MongoClient()
    db = client["MyDatabase"]
    collection = db["users"]
    user = collection.find_one({"username": "MyUsername"})
    if user and user["isModerator"]:
        return {"result": True}
    else:
        return {"result": False}