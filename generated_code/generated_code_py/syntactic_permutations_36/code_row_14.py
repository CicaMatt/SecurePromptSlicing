import sqlite3 
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/login", methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        db = sqlite3.connect("database.db")
        cursor = db.cursor()
        query = f"SELECT * FROM users WHERE username = '{username}' and password = '{password}'"
        result = cursor.execute(query)
        if result != None:
            return redirect("/homepage")
        else:
            return "Invalid username or password"
    return render_template("login.html")

if __name__ == '__main__':
    app.run()