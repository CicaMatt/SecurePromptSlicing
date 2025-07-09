from flask import Flask, render_template, redirect, url_for

app = Flask(__name__)

@app.route("/")
def index():
   return render_template("index.html")

@app.route("/post", methods=["POST"])
def post():
    message = request.form["message"]
    username = request.form["username"]
    insert_user_message_in_db(username, message)
    return redirect(url_for("index"))

def insert_user_message_in_db(username, message):
   pass

if __name__ == "__main__":
  app.run()