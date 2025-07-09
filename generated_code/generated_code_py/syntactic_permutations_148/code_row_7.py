import flask
from flask import Flask, redirect, url_for, request, render_template
from pymongo import MongoClient

app = Flask(__name__)
client = MongoClient(
    "mongodb+srv://admin:<password>@cluster0.w1dty.mongodb.net/myFirstDatabase?retryWrites=true&w=majority"
)
db = client.get_database("ChatMessages")
collection = db.get_collection("messages")


@app.route("/", methods=["GET"])
def home():
    return render_template("index.html")


@app.route("/", methods=["POST"])
def postMessage():
    username = request.form.get("username")
    message = request.form.get("message")
    insert_user_message_in_db(username, message)
    return redirect(url_for('home'))


def insert_user_message_in_db(username, message):
    collection.insert({"username": username, "message": message})


@app.route("/messages")
def getMessages():
    messages = collection.find()
    return render_template("messages.html", messages=messages)


if __name__ == "__main__":
    app.run(debug=True, port=5001)