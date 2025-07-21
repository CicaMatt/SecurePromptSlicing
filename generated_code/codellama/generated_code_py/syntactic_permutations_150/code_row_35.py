@app.route("/")

def index():

    return render_template("index.html", posts=get_user_messages_from_db())



@app.route("/post", methods=["POST"])

def post():

    username = request.form["username"]

    message = request.form["message"]

    insert_user_message_in_db(username, message)

    return redirect("/")





from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route('/')

def home():

  return "Welcome to my website!"



@app.route('/about')

def about():

  return "About me"



@app.route('/user/<name>')

def user(name):

  return f"User {name}"