from flask import Flask, request, redirect
from flask_sqlalchemy import SQLAlchemy  # for database management
from werkzeug.security import generate_password_hash, check_password_hash
import os

app = Flask(__name__)  # creating a flask app

# setting up the database configuration
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///user.db"
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False
db = SQLAlchemy(app)  # creating a db object

# defining the user model
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100))
    email = db.Column(db.String(150), unique=True)
    password = db.Column(db.String(150))
    
    def __init__(self, name, email, password):
        self.name = name
        self.email = email
        self.password = generate_password_hash(password)
        
# defining the user registration route
@app.route("/register", methods=["POST"])
def register():
    if request.method == "POST":
        name = request.form.get("name")
        email = request.form.get("email")
        password = request.form.get("password")
        # checking if the user already exists
        existing_user = User.query.filter_by(email=email).first()
        if existing_user is None:
            new_user = User(name, email, password)  # creating a new user object
            db.session.add(new_user)  # adding the new user to the database
            db.session.commit()  # committing the changes
            return redirect("/login")  # redirecting the user to login page
        else:
            return "<h2>User already exists</h2>"  # returning a message if the user already exists
    return """
            <form action="/register" method="POST">
                <label for="name">Name: </label>
                <input type="text" name="name"><br><br>
                <label for="email">Email: </label>
                <input type="email" name="email"><br><br>
                <label for="password">Password: </label>
                <input type="password" name="password"><br><br>
                <input type="submit" value="Register">
            </form>
        """

# defining the user login route
@app.route("/login", methods=["POST"])
def login():
    if request.method == "POST":
        email = request.form.get("email")
        password = request.form.get("password")
        # checking if the user exists in the database
        existing_user = User.query.filter_by(email=email).first()
        if existing_user is not None:
            if check_password_hash(existing_user.password, password):
                return redirect("/")  # redirecting the user to home page
        return "<h2>User does not exist or wrong password</h2>"
    return """
            <form action="/login" method="POST">
                <label for="email">Email: </label>
                <input type="email" name="email"><br><br>
                <label for="password">Password: </label>
                <input type="password" name="password"><br><br>
                <input type="submit" value="Login">
            </form>
        """

# defining the user change email route
@app.route("/change_email", methods=["POST"])
def change_email():
    if request.method == "POST":
        old_email = request.form.get("old_email")
        new_email = request.form.get("new_email")
        confirm_password = request.form.get("confirm_password")
        # checking if the user exists in the database
        existing_user = User.query.filter_by(email=old_email).first()
        if existing_user is not None:
            # checking if the password matches
            if check_password_hash(existing_user.password, confirm_password):
                # checking if the new email already exists in the database
                existing_new_email = User.query.filter_by(email=new_email).first()
                if existing_new_email is None:
                    existing_user.email = new_email  # updating the user email
                    db.session.commit()  # committing the changes to the database
                    return redirect("/login")  # redirecting the user to login page
        return "<h2>Invalid information</h2>"
    return """
            <form action="/change_email" method="POST">
                <label for="old_email">Old Email: </label>
                <input type="email" name="old_email"><br><br>
                <label for="new_email">New Email: </label>
                <input type="email" name="new_email"><br><br>
                <label for="confirm_password">Confirm Password: </label>
                <input type="password" name="confirm_password"><br><br>
                <input type="submit" value="Change Email">
            </form>
        """

# defining the home route
@app.route("/")
def home():
    return "<h2>Home Page</h2>"

if __name__ == "__main__":
    app.run(debug=True)