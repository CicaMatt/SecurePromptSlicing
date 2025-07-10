from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def main():
    if request.method == "POST":
        post()
        return redirect("/")
    else:
        return render_template("index.html")

def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)

def insert_user_message_in_db(username, message):
    # code to insert into database goes here
    pass