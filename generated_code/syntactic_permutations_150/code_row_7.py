from flask import Flask, redirect, url_for, request
app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return "<form action='post'><label>Username:<input type="text" name="username"></label><br>
                  <label>Message:<textarea type="text" name="message"></textarea></label><br>
                  <button type="submit">Submit</button></form>"
    else:
        username = request.form["username"]
        message = request.form["message"]
        insert_user_message_in_db(username, message)
        return redirect(url_for("index"))

def insert_user_message_in_db(username, message):
    # code to connect to database and insert username and message into a table.
    pass