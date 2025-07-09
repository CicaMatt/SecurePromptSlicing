from flask import Flask, request, redirect
app = Flask(__name__)

import pymongo
client = pymongo.MongoClient("mongodb://localhost:27017/")
db = client["chat_app"]
messages_collection = db["messages"]

def insert_user_message_in_db(username, message):
    messages_collection.insert_one({"username": username, "message": message})

@app.route("/post", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect("/")

@app.route("/")
def show_messages():
    messages = list(messages_collection.find())
    return render_template("index.html", messages=messages)

if __name__ == "__main__":
    app.run(debug=True)