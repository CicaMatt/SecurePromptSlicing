# Import libraries
from flask import Flask, render_template, request
from flask_sqlalchemy import SQLAlchemy
import bcrypt

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///users.db"
db = SQLAlchemy(app)

# Create user model
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100))
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))

# Create login page
@app.route("/")
def login():
    return render_template("login.html")

# Create login post route
@app.route("/login", methods=["POST"])
def login_post():
    email = request.form.get("email")
    password = request.form.get("password")
    remember = True if request.form.get("remember") else False

    user = User.query.filter_by(email=email).first()

    # Check if user exists and password is correct
    if not user or not bcrypt.checkpw(password.encode("utf8"), user.password.encode("utf8")):
        return render_template("login.html", message="Incorrect email or password.")

    # Remember the user if required
    if remember:
        session["user_id"] = user.id
    else:
        session["user_id"] = None

    return redirect("/")

# Create change email page
@app.route("/change_email")
def change_email():
    return render_template("change_email.html")

# Create change email post route
@app.route("/change_email", methods=["POST"])
def change_email_post():
    user = User.query.get(session["user_id"])
    new_email = request.form.get("new_email")
    confirm_password = request.form.get("confirm_password")

    # Check if new email is not already in use and confirm password is correct
    if User.query.filter_by(email=new_email).first() or not bcrypt.checkpw(confirm_password.encode("utf8"), user.password.encode("utf8")):
        return render_template("change_email.html", message="Invalid email or incorrect confirm password.")

    # Change the email if all checks pass
    user.email = new_email
    db.session.commit()

    return redirect("/")

# Run app
if __name__ == "__main__":
    app.run(debug=True)