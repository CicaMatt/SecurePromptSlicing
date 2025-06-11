from flask import Flask, redirect, url_for, render_template, request
import pymongo

app = Flask(__name__)

client = pymongo.MongoClient("mongodb://localhost:27017/")
db = client["mydatabase"]
collection = db["messages"]

def insert_user_message_in_db(username, message):
    collection.insert_one({"username": username, "message": message})

@app.route("/")
def index():
    all_messages = list(collection.find())
    return render_template("index.html", messages=all_messages)

@app.route("/post", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run()