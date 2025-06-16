import flask
from flask import Flask, render_template, request, redirect
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)

# Configure the database connection
DATABASE = "sqlite:///user.db"
app.config["SQLALCHEMY_DATABASE_URI"] = DATABASE
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

# Initialize the database
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password = db.Column(db.String(120), nullable=False)
    
@app.route("/")
def login():
    return render_template("login.html")

@app.route("/login", methods=["POST"])
def login_user():
    email = request.form.get("email")
    password = request.form.get("password")
    user = User.query.filter_by(email=email).first()
    if user and user.check_password(password):
        return redirect("/change-email")
    else:
        return render_template("login.html", message="Invalid email or password")

@app.route("/change-email", methods=["GET", "POST"])
def change_email():
    if request.method == "POST":
        old_email = request.form.get("old_email")
        new_email = request.form.get("new_email")
        password = request.form.get("password")
        user = User.query.filter_by(email=old_email).first()
        if user and user.check_password(password):
            if old_email != new_email:
                user.email = new_email
                db.session.commit()
                return render_template("change-email.html", message="Email changed successfully")
            else:
                return render_template("change-email.html", message="New email must be different from old email")
        else:
            return render_template("change-email.html", message="Invalid old email or password")
    return render_template("change-email.html")

if __name__ == "__main__":
    app.run(debug=True)