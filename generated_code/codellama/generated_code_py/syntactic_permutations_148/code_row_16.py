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
