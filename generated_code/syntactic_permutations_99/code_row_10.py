import os
import hashlib
from flask import Flask, session, redirect, url_for, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///data.db"
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password = db.Column(db.String(120), nullable=False)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        username = request.form["username"]
        password = hashlib.sha256(request.form["password"].encode()).hexdigest()
        user = User(username=username, password=password)
        db.session.add(user)
        db.session.commit()
        return redirect(url_for("login"))
    else:
        return """
        <form method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password"><br><br>
            <input type="submit" value="Register">
        </form>"""

if __name__ == "__main__":
    app.run(debug=True)

### Explanation: 
The code uses Flask to create a simple web application. The `User` class is used to define the database model for the user table with columns `id`, `username`, and `password`. The password is hashed using SHA-256 before being stored in the database. The login form takes input from the user and inserts it into the `User` table.

### Additional info:
The output code may contain additional information such as comments or documentation strings, but they should not affect the functionality of the code.