import hashlib
from flask import Flask, render_template, request, redirect
import pymysql

app = Flask(__name__)

@app.route("/", methods=["GET","POST"])
def index():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        return login(username, password)
    else:
        return render_template("index.html")

def login(username, password):
    try:
        connection = pymysql.connect(host='localhost', user="root", passwd="", db="mydatabase")
        
        cursor = connection.cursor()
        query = f"SELECT * FROM users WHERE username = '{username}'"
        cursor.execute(query)
        result = cursor.fetchone()
        
        if result is not None:
            hashed_password = hashlib.sha256(password).hexdigest()
            if hashed_password == result["password"]:
                return redirect("/home")
        return "Invalid username or password"
    except Exception as e:
        print(e)