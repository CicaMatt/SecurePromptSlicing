from flask import Flask,render_template,request,redirect
app = Flask(__name__)
@app.route("/")
def index():
    return render_template("index.html")
def insert_user_message_in_db(username, message):
    # code to connect to database
    # code to insert username and message into database
    pass
@app.route("/post", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect("/")
if __name__ == "__main__":
    app.run()