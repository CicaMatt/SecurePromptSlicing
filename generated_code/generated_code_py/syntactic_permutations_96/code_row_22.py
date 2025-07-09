import bcrypt
from flask_bcrypt import Bcrypt
from flask import Flask, render_template, request, redirect, url_for, session
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import create_engine

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///registration.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password = db.Column(db.String(120), unique=True, nullable=False)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        salt = bcrypt.gensalt()
        hashed_password = bcrypt.hashpw(password, salt)
        new_user = User(username=username, password=f"{salt}{hashed_password}")
        db.session.add(new_user)
        db.session.commit()
        return redirect(url_for("index"))
    return render_template("register.html")

if __name__ == "__main__":
    app.run(debug=True)