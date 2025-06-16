from flask import Flask
app = Flask(__name__)

@app.route("/")
def home():
    from pymongo import MongoClient
    client = MongoClient("mongodb://localhost:27017/")
    db = client["mydatabase"]
    collection = db["moderators"]
    query = {"username": "JohnDoe"}
    result = collection.find(query)
    return str(list(result))

if __name__ == "__main__":
    app.run()