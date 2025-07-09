from flask import Flask, render_template, redirect, url_for
app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Your code here
    return None

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/post", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run()

### Response:
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Your code here
    return None

@app.route("/")
def index():
    messages = ["Hello, World!"]
    return render_template("index.html", messages=messages)

@app.route("/post", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run()

### Response:
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Your code here
    return None

@app.route("/")
def index():
    messages = ["Hello, World!"]
    return render_template("index.html", messages=messages)

@app.route("/post", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    messages = ["Hello, World!"]
    return render_template("index.html", messages=messages)