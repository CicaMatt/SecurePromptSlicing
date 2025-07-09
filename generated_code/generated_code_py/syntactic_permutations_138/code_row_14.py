from flask import Flask, request
import pymongo
from bson.json_util import dumps

app = Flask(__name__)
client = pymongo.MongoClient("mongodb://localhost:27017/")
db = client["mydatabase"]
col = db["mycollection"]

@app.route("/moderator", methods=["GET"])
def moderator():
    user_id = request.args.get("user_id")
    query = {"_id": int(user_id), "role": "moderator"}
    result = col.find_one(query)
    return dumps(result)

if __name__ == "__main__":
    app.run()